import * as React from "react";
import { Router, Route, browserHistory } from "react-router";

import * as HomeRoute from "./lib/es6/src/components/HomeRoute";

import * as PackageDetailsRoute from "./lib/es6/src/components/PackageDetailsRoute";
import * as PackageIndexRoute from "./lib/es6/src/components/PackageIndexRoute";

import * as KeywordIndexRoute from "./lib/es6/src/components/KeywordIndexRoute";
import * as KeywordDetailsRoute from "./lib/es6/src/components/KeywordDetailsRoute";

import * as PublishRoute from "./lib/es6/src/components/PublishRoute";

const {
  createContainer,
} = require("@phenomic/preset-react-app/lib/es6/src/phenomicPresetReactApp.js");

export const routes = () => (
  <Router history={browserHistory}>
    <Route
      path="/"
      component={createContainer(HomeRoute.jsComponent, HomeRoute.queries)}
    />
    <Route path="/publish" component={PublishRoute.jsComponent} />
    <Route
      path="/packages"
      component={createContainer(
        PackageIndexRoute.jsComponent,
        PackageIndexRoute.queries
      )}
    />
    <Route
      path="/packages/*"
      component={createContainer(
        PackageDetailsRoute.jsComponent,
        PackageDetailsRoute.queries
      )}
    />
    <Route
      path="/keywords"
      component={createContainer(
        KeywordIndexRoute.jsComponent,
        KeywordIndexRoute.queries
      )}
    />
    <Route
      path="/keywords/:keywords"
      component={createContainer(
        KeywordDetailsRoute.jsComponent,
        KeywordDetailsRoute.queries
      )}
    />
    <Route path="*" component={() => <div> Not found </div>} />
  </Router>
);
