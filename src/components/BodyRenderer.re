let component = ReasonReact.statelessComponent("BodyRenderer");

let make = (~body: string, _children) => {
  ...component,
  render: (_) => <div dangerouslySetInnerHTML={"__html": body} />
};