import * as React from "react";
import { createApp, renderApp } from "@phenomic/preset-react-app/lib/client";
import { css, rehydrate } from "glamor";

if (typeof window !== "undefined" && window._glam) {
  rehydrate(window._glam);
}
// Must put everything that uses glamor inside a file
// for rehydrate to work
const routes = require("./Routes").routes;

export default createApp(routes);

if (module.hot) {
  module.hot.accept(() => renderApp(routes));
}
