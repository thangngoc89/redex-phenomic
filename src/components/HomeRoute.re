open Helpers;

module Styles = IndexStyles;

let component = ReasonReact.statelessComponent("Home");

type package = Typings.package;

type keyword = Typings.keyword;

let make =
    (
      ~popularPackages: PhenomicPresetReactApp.edge(array(package)),
      ~recentPackages: PhenomicPresetReactApp.edge(array(package)),
      ~keywords: PhenomicPresetReactApp.edge(array(keyword)),
      _children
    ) => {
  ...component,
  render: _self =>
    <HomeLayout>
      <div className=Styles.root>
        <SearchBox />
        <DataLoading
          data=keywords
          renderIdle=(
            keywords =>
              <div className=Styles.keywords>
                <Control.Map items=keywords>
                  ...(
                       keyword =>
                         <Link
                           key=keyword##name
                           href=("/keywords/" ++ keyword##name)>
                           <span className="label">
                             (keyword##name |> text)
                           </span>
                           <span className="count">
                             (keyword##count |> string_of_int |> text)
                           </span>
                         </Link>
                     )
                </Control.Map>
              </div>
          )
        />
        <div className=Styles.lists>
          <div>
            <h2> ("Recent releases" |> text) </h2>
            <DataLoading
              data=recentPackages
              renderIdle=(packages => <TopList packages value=`updated />)
            />
          </div>
          <div>
            <h2> ("Most popular" |> text) </h2>
            <DataLoading
              data=popularPackages
              renderIdle=(packages => <TopList packages value=`stars />)
            />
          </div>
        </div>
      </div>
    </HomeLayout>
};

let doNothing = a => a;

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~popularPackages=
        PhenomicPresetReactApp.jsEdgeToReason(
          jsProps##popularPackages, packages =>
          packages##list
        ),
      ~recentPackages=
        PhenomicPresetReactApp.jsEdgeToReason(
          jsProps##recentPackages, packages =>
          packages##list
        ),
      ~keywords=
        PhenomicPresetReactApp.jsEdgeToReason(jsProps##keywords, a => a##data),
      [||]
    )
  );

let queries = (_) => {
  let popularPackages =
    PhenomicPresetReactApp.query(
      List({
        path: "packages",
        by: Some("default"),
        value: None,
        order: Some("asc"),
        limit: Some(10)
      })
    );
  let recentPackages =
    PhenomicPresetReactApp.query(
      List({
        path: "packages",
        by: Some("type"),
        value: Some("published"),
        order: Some("desc"),
        limit: Some(10)
      })
    );
  let keywords =
    PhenomicPresetReactApp.query(
      Item({path: "", id: "keywords-sort-count-desc"})
    );
  {
    "popularPackages": popularPackages,
    "recentPackages": recentPackages,
    "keywords": keywords
  };
};