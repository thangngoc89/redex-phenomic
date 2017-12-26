open Helpers;

module Styles = PackageStyles;

let component = ReasonReact.statelessComponent("Package");

type package = Typings.package;

let renderIdle = package =>
  <div className=Styles.root>
    <Helmet title=(Config.titleTemplate(package##name))>
      <link href="/highlight.css" rel="stylesheet" />
    </Helmet>
    <header className=(Styles.header(package##_type))>
      <div className=Styles.props>
        <Control.IfSome option=(package##stars |> Js.toOption)>
          ...(
               stars =>
                 <div className=Styles.stars>
                   (stars |> text)
                   <Icon.Star className=Styles.starIcon />
                 </div>
             )
        </Control.IfSome>
        <Score package />
        (
          switch (package##license |> Js.toOption) {
          | Some(license) =>
            <div className=Styles.license> (license |> text) </div>
          | None =>
            <div className=Styles.nolicense> ("No license" |> text) </div>
          }
        )
        <div className=Styles.updated> <TimeAgo date=package##updated /> </div>
      </div>
      <div className=Styles.title>
        /*<span className=Styles.owner> {"package" |> text} </span>*/

          <Link href=("/packages/" ++ package##id) className=Styles.name>
            (package##name |> text)
          </Link>
          <span className=Styles.version> (package##version |> text) </span>
          (
            switch package##_type {
            | "unpublished" =>
              <span className=Styles.unpublishedLabel>
                ("unpublished" |> text)
              </span>
            | _ => ReasonReact.nullElement
            }
          )
        </div>
      <div className=Styles.fields>
        <div className=Styles.description>
          (package##description |> text)
        </div>
        <div className=Styles.tags>
          <Icon.Tags className=Styles.tagsIcon />
          <Control.Map items=package##keywords empty=(" - " |> text)>
            ...(keyword => <Tag key=keyword name=keyword />)
          </Control.Map>
        </div>
      </div>
      <div className=Styles.links>
        <a href=?(Js.toOption(package##homepageUrl))> ("homepage" |> text) </a>
        <a href=?(Js.toOption(package##repositoryUrl))>
          ("repository" |> text)
        </a>
        <a href=?(Js.toOption(package##npmUrl))> ("npm" |> text) </a>
        <a href=?(Js.toOption(package##issuesUrl))> ("issues" |> text) </a>
        <a href=?(Js.toOption(package##docsUrl))>
          ("documentation" |> text)
        </a>
      </div>
    </header>
    <div
      className=Styles.readme
      dangerouslySetInnerHTML={"__html": package##body}
    />
  </div>;

let make = (~push, ~package, _) => {
  ...component,
  render: _self =>
    <IndexLayout push> <DataLoading data=package renderIdle /> </IndexLayout>
};

/* TODO: fix upstream package to allow not passing a converter */
let doNothing = a => a;

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~package=
        PhenomicPresetReactApp.jsEdgeToReason(jsProps##package, doNothing),
      ~push=jsProps##router##push,
      [||]
    )
  );

let queries = props => {
  let package =
    PhenomicPresetReactApp.query(
      Item({path: "packages", id: props##params##package})
    );
  {"package": package};
};