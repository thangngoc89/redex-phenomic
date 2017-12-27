const path = require("path");
const unified = require("unified");
const markdown = require("remark-parse");
const highlight = require("remark-highlight.js");
const toc = require("remark-toc");
const remarkRehype = require("remark-rehype");
const raw = require("rehype-raw");
const slug = require("rehype-slug");
const autoLinkHeadings = require("rehype-autolink-headings");
const html = require("rehype-stringify");
const rehype2react = require("rehype-react");

function mdTransform(config, body) {
  const processor = unified()
    .use(markdown)
    .use(highlight)
    .use(remarkRehype, { allowDangerousHTML: true })
    .use(raw)
    .use(slug)
    .use(autoLinkHeadings)
    .use(html);

  return processor.processSync(body);
}

function transformJSONFile({ config, file, contents }) {
  const parsedContents = JSON.parse(contents.toString());
  const data = Object.assign({}, parsedContents, {
    path: file.name.startsWith("packages/")
      ? "packages/" + parsedContents.id
      : path.basename(file.name, ".json"),
  });
  data.body = mdTransform(config, data.body).contents;

  const partial = _objectWithoutProperties(data, ["body"]);

  return {
    data,
    partial,
  };
}

module.exports = function() {
  return {
    name: "redex-transformer-json",
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
