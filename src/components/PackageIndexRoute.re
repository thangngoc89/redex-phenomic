open Helpers;

let component = ReasonReact.statelessComponent("Home");

type package = Typings.package;

let renderIdle = packages =>
  <Control.Map items=packages>
    ...(package => <PackageSummary key=package##id package />)
  </Control.Map>;

let make = (~packages: PhenomicPresetReactApp.edge(array(package))) => {
  ...component,
  render: _self =>
    <IndexLayout>
      <Fragment>
        <Helmet title=(Config.titleTemplate("Packages")) />
        <h1> ("Packages" |> text) </h1>
        <DataLoading data=packages renderIdle />
      </Fragment>
    </IndexLayout>
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
        limit: None
      })
    );
  {"packages": packages};
};