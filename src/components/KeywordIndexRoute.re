open Helpers;

let component = ReasonReact.statelessComponent("Home");

type keyword = Typings.keyword;

type package = Typings.package;

/* TODO: figure out how to pass the compiler on this */
let getPackages: (array(string), array(package)) => array(package) = [%bs.raw
  {|
    function(packageName, allPackages) {
      return packageName.map((name) => {
        return allPackages.find((pkg) => pkg.name === name)
      })
    }
    |}
];

let renderIdle = (~keywords: array(keyword), ~allPackages: array(package)) =>
  <Control.Map items=keywords>
    ...(
         keyword =>
           <div key=keyword##name>
             <h2> (keyword##name |> text) </h2>
             <Control.Map items=(getPackages(keyword##packages, allPackages))>
               ...(package => <PackageSummary key=package##id package />)
             </Control.Map>
           </div>
       )
  </Control.Map>;

let make =
    (
      ~allPackages: PhenomicPresetReactApp.edge(array(package)),
      ~keywords: PhenomicPresetReactApp.edge(array(keyword)),
      ~push
    ) => {
  ...component,
  render: _self =>
    <IndexLayout push>
      <Helmet title=(Config.titleTemplate("Keywords")) />
      <h1> ("Keywords" |> text) </h1>
      (
        switch (allPackages, keywords) {
        | (Inactive, _)
        | (_, Inactive)
        | (Loading, _)
        | (_, Loading) => "Loading..." |> text
        | (Errored, _)
        | (_, Errored) => "An error occured" |> text
        | (Idle(allPackages), Idle(keywords)) =>
          renderIdle(~allPackages, ~keywords)
        }
      )
    </IndexLayout>
};

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~allPackages=
        PhenomicPresetReactApp.jsEdgeToReason(jsProps##allPackages, a =>
          a##list
        ),
      ~keywords=
        PhenomicPresetReactApp.jsEdgeToReason(jsProps##keywords, a => a##data),
      ~push=jsProps##router##push
    )
  );

let queries = (_) => {
  let keywords =
    PhenomicPresetReactApp.query(
      Item({path: "", id: "keywords-sort-name-asc"})
    );
  let packages =
    PhenomicPresetReactApp.query(
      List({
        path: "packages",
        by: Some("default"),
        value: None,
        order: Some("asc"),
        limit: None
      })
    );
  {"keywords": keywords, "allPackages": packages};
};