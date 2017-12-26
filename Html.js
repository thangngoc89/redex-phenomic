import * as React from "react";
import { renderStaticOptimized } from "glamor/server";
import Head from "react-helmet";

export default ({ App, render }) => {
  const { html, Main, State, Script } = render(<App />);
  const { css, ids } = renderStaticOptimized(() => html);
  const helmet = Head.renderStatic();
  return (
    <html {...helmet.htmlAttributes.toComponent()}>
      <head>
        <meta charSet="utf-8" />
        <meta httpEquiv="x-ua-compatible" content="ie=edge" />
        <meta
          name="viewport"
          content="width=device-width, initial-scale=1, shrink-to-fit=no"
        />
        <link href="/reset.css" rel="stylesheet" />
        {helmet.meta.toComponent()}
        {helmet.title.toComponent()}
        {helmet.base.toComponent()}
        {helmet.link.toComponent()}
        {helmet.style.toComponent()}
        {helmet.script.toComponent()}
        {helmet.noscript.toComponent()}
        <style dangerouslySetInnerHTML={{ __html: css }} />
      </head>
      <body>
        <Main />
        <State />
        <script
          dangerouslySetInnerHTML={{
            __html: `window._glam = ${JSON.stringify(ids)}`,
          }}
        />
        <Script />
      </body>
    </html>
  );
};
