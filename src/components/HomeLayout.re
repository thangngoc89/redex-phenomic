open! Helpers;

module Styles = HomeLayoutStyles;

let component = ReasonReact.statelessComponent("FrontPageLayout");

let make = children => {
  ...component,
  render: _self =>
    <div className=Styles.root>
      <Helmet title="redex | Reason Package Index">
        <html lang="en" />
        <meta
          name="description"
          content="Package index for the ReasonML/BuckleScript ecosystem"
        />
      </Helmet>
      <div className=Styles.links>
        <div className=CommonStyles.widthContainer>
          <span className="left" />
          <Link href="/packages"> ("Packages" |> text) </Link>
          <Link href="/keywords"> ("Keywords" |> text) </Link>
          <Link href="/packages/unpublished"> ("Unpublished" |> text) </Link>
          <Link className=Styles.inactiveLink href="/">
            ("Documentation" |> text)
          </Link>
          <span className="right">
            <Link className=Styles.publishLink href="/publish">
              ("Get Published" |> text)
            </Link>
          </span>
        </div>
      </div>
      <div className=Styles.header>
        <div className=CommonStyles.widthContainer>
          <h1 className=Styles.title>
            <svg className=Styles.logo>
              /* NOTE: xlink stuff needed for safari */

                <use
                  href="/logo.svg#logo"
                  xmlnsXlink="http://www.w3.org/1999/xlink"
                  xlinkHref="/logo.svg#logo"
                />
              </svg>
            <em> ("re" |> text) </em>
            ("ason package in" |> text)
            <em> ("dex" |> text) </em>
          </h1>
        </div>
      </div>
      (
        ReasonReact.createDomElement(
          "div",
          ~props={"className": CommonStyles.widthContainer},
          children
        )
      )
      <Footer context=`Front />
    </div>
};