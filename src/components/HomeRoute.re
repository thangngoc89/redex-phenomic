open Helpers;

module Styles = IndexStyles;

let component = ReasonReact.statelessComponent("Home");

type package = Typings.package;

let renderIdle = (packages: array(package)) =>
  <div className=Styles.lists>
    <div>
      <h2> ("Recent releases" |> text) </h2>
      <TopList packages value=`updated />
    </div>
    <div>
      <h2> ("Most popular" |> text) </h2>
      <TopList packages value=`stars />
    </div>
  </div>;

let make = (~packages: PhenomicPresetReactApp.edge(array(package))) => {
  ...component,
  render: _self =>
    <HomeLayout>
      <div className=Styles.root>
        <SearchBox />
        /*<div className=Styles.keywords>
            <Control.Map items=(keywords)>
              ...(
                   keyword =>
                     <Link key=keyword##slug href=keyword##slug>
                       <span className="label"> (keyword##name |> text) </span>
                       <span className="count"> (keyword##count |> text) </span>
                     </Link>
                 )
            </Control.Map>
          </div> */
        <DataLoading data=packages renderIdle />
      </div>
    </HomeLayout>
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