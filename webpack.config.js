import path from "path";

import webpack from "webpack";
import ExtractTextPlugin from "extract-text-webpack-plugin";
import FriendlyErrorsWebpackPlugin from "friendly-errors-webpack-plugin";
import HardSourceWebpackPlugin from "hard-source-webpack-plugin";

module.exports = config => ({
  entry: {
    [config.bundleName]: [
      process.env.PHENOMIC_ENV !== "static" &&
        require.resolve("webpack-hot-middleware/client"),
      process.env.PHENOMIC_ENV !== "static" &&
        require.resolve("react-hot-loader/patch"),
      "./App.js",
    ].filter(item => item),
  },
  output: Object.assign(
    {
      publicPath: "/", // @todo make this dynamic
      path: path.isAbsolute(config.outdir)
        ? config.outdir
        : path.join(process.cwd(), config.outdir),
    },
    process.env.PHENOMIC_ENV !== "static"
      ? {
          filename: "phenomic/[name].js",
          chunkFilename: "phenomic/[name].chunk.js",
        }
      : {
          filename: "phenomic/[name].[chunkhash:8].js",
          chunkFilename: "phenomic/[name].[chunkhash:8].chunk.js",
        }
  ),
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /node_modules/,
        loader: require.resolve("babel-loader"),
        options: {
          babelrc: false,
          presets: [require.resolve("@phenomic/babel-preset")],
          plugins: [require.resolve("react-hot-loader/babel")],
        },
      },
    ],
  },
  plugins: [
    new HardSourceWebpackPlugin({
      configHash: function(webpackConfig) {
        return require("node-object-hash")({ sort: false }).hash({
          phenomic: config,
          webpack: webpackConfig,
        });
      },
      environmentHash: {
        root: process.cwd(),
        directories: [],
        files: [
          "webpack.config.js",
          "phenomic.config.js",
          "package.json",
          "yarn.lock",
        ],
      },
    }),
    new FriendlyErrorsWebpackPlugin(),
    process.env.PHENOMIC_ENV !== "static" &&
      new webpack.HotModuleReplacementPlugin(),
    process.env.NODE_ENV === "production" &&
      new webpack.optimize.UglifyJsPlugin(),
  ].filter(item => item),

  resolve: {
    extensions: [".js", ".json"],
  },

  // eslint-disable-next-line max-len
  // https://github.com/facebookincubator/create-react-app/blob/fbdff9d722d6ce669a090138022c4d3536ae95bb/packages/react-scripts/config/webpack.config.prod.js#L279-L285
  node: {
    fs: "empty",
    net: "empty",
    tls: "empty",
  },
});
