open Helpers;

let component = ReasonReact.statelessComponent("DataLoading");

let make =
    (
      ~data: PhenomicPresetReactApp.edge('a),
      ~renderIdle,
      ~renderLoading=?,
      ~renderError=?,
      _
    ) => {
  ...component,
  render: _self =>
    <Fragment>
      (
        switch data {
        | Inactive
        | Loading =>
          switch renderLoading {
          | Some(a) => a()
          | None => "Loading ..." |> text
          }
        | Errored =>
          switch renderError {
          | Some(a) => a()
          | None => "An error occured" |> text
          }
        | Idle(data) => renderIdle(data)
        }
      )
    </Fragment>
};