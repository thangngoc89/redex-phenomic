open Helpers;

let component = ReasonReact.statelessComponent("Home");

type package = {
  .
  "id": string,
  "name": string
};

let renderIdle = packages =>
  <ul>
    (
      packages
      |> Array.map(item =>
           <li key=item##id>
             <Link href=("packages/" ++ item##id ++ "/")>
               (item##name |> text)
             </Link>
           </li>
         )
      |> ReasonReact.arrayToElement
    )
  </ul>;

let make = (~packages: PhenomicPresetReactApp.edge(array(package))) => {
  ...component,
  render: _self =>
    <HomeLayout> <DataLoading data=packages renderIdle /> </HomeLayout>
};

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~packages=
        PhenomicPresetReactApp.jsEdgeToReason(jsProps##packages, packages =>
          packages##list
        )
    )
  );

let queries = (_) => {
  let packages =
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
        order: Some("asc"),
        limit: Some(10)
      })
    );
  {"packages": packages};
};