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

module.exports = (config, body) => {
  const processor = unified()
    .use(markdown)
    .use(highlight)
    .use(remarkRehype, { allowDangerousHTML: true })
    .use(raw)
    .use(slug)
    .use(autoLinkHeadings)
    .use(html);

  return processor.processSync(body);
};
