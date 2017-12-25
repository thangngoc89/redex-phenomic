const bundlerWebpack = require("@phenomic/plugin-bundler-webpack");
const rendererReact = require("@phenomic/plugin-renderer-react");
const collectorFiles = require("@phenomic/plugin-collector-files");
const transformJson = require("./transformJson");
const apiRelatedContent = require("@phenomic/plugin-api-related-content");
const publicAssets = require("@phenomic/plugin-public-assets");

module.exports = {
  plugins: [
    bundlerWebpack,
    rendererReact,
    transformJson,
    collectorFiles,
    apiRelatedContent,
    publicAssets,
  ],
};
