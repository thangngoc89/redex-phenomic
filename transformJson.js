const path = require("path");
const remarkProcess = require("./markdownTransformer");

function transformJSONFile({ config, file, contents }) {
  const data = Object.assign({}, JSON.parse(contents.toString()), {
    path: path.basename(file.name, ".json"),
  });
  data.body = remarkProcess(config, data.body).contents;

  const partial = _objectWithoutProperties(data, ["body"]);

  return {
    data,
    partial,
  };
}

module.exports = function() {
  return {
    name: "@phenomic/plugin-transform-json",
    supportedFileTypes: ["json"],
    transform: transformJSONFile,
  };
};

function _objectWithoutProperties(obj, keys) {
  var target = {};
  for (var i in obj) {
    if (keys.indexOf(i) >= 0) continue;
    if (!Object.prototype.hasOwnProperty.call(obj, i)) continue;
    target[i] = obj[i];
  }
  return target;
}
