open Helpers;

/* open Rebase; */
let component = ReasonReact.statelessComponent("Home");

type keyword = Typings.keyword;

/* TODO: figure out how to pass the compiler on this */
/* let getPackages = keyword =>
   keyword##packages
   |> Array.map(Js.toOption)
   |> Array.filter(
        fun
        | Some(_) => true
        | None => {
            Js.log("missing package on keyword: " ++ keyword##name);
            false;
          }
      )
   |> Array.map(Option.getOrRaise)
   |> Js.Array.sortInPlaceWith((a, b) => compare(a##name: string, b##name)); */
let renderIdle = (keywords: array(keyword)) =>
  <Control.Map items=keywords>
    ...(
         keyword =>
           <div key=keyword##name>
             <h2> (keyword##name |> text) </h2>
             <Control.Map items=keyword##packages>
               ...(package => <div key=package> (package |> text) </div>)
             </Control.Map>
           </div>
           /* <Control.Map items=keyword##packages>
                ...(package => <PackageSummary key=package##id package />)
              </Control.Map> */
       )
  </Control.Map>;

let make = (~push, ~keywords: PhenomicPresetReactApp.edge(array(keyword))) => {
  ...component,
  render: _self =>
    <IndexLayout push>
      <Helmet title=(Config.titleTemplate("Keywords")) />
      <h1> ("Keywords" |> text) </h1>
      <DataLoading data=keywords renderIdle />
    </IndexLayout>
};

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
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
  {"keywords": keywords};
};