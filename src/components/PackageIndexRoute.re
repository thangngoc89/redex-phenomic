open Helpers;

let component = ReasonReact.statelessComponent("Home");

/* TODO: Where the heck is this type def ? */
type package = {
  .
  "_type": string,
  "description": string,
  "id": string,
  "keywords": array(string),
  "license": Js.nullable(string),
  "maintenance": float,
  "name": string,
  "popularity": float,
  "quality": float,
  "slug": string,
  "score": float,
  "stars": Js.nullable(string),
  "updated": Js.Date.t,
  "version": string
};

let make = (~packages: PhenomicPresetReactApp.edge(array(package))) => {
  ...component,
  render: _self =>
    <IndexLayout>
      <Fragment>
        <Helmet title=(Config.titleTemplate("Packages")) />
        <h1> ("Packages" |> text) </h1>
        (
          switch packages {
          | Inactive
          | Loading => "Loading ..." |> text
          | Errored => "An error occured" |> text
          | Idle(packages) =>
            <Control.Map items=packages>
              ...(package => <PackageSummary key=package##id package />)
            </Control.Map>
          }
        )
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