const keywords = require("../content/keywords.json").data;
const fs = require("fs");
const path = require("path");

function sortBy(sort) {
  return (a, b) => {
    a = a[sort];
    b = b[sort];
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    if (b > a) return -1;
    if (a > b) return 1;
    return 0;
  };
}

const byCount = [...keywords].sort(sortBy("count")).reverse();
const byName = [...keywords].sort(sortBy("name"));

console.log(byCount === byName);
fs.writeFileSync(
  path.join(__dirname, "../content", "keywords-sort-count-desc.json"),
  JSON.stringify({ data: byCount }, null, 2)
);
fs.writeFileSync(
  path.join(__dirname, "../content", "keywords-sort-name-asc.json"),
  JSON.stringify({ data: byName }, null, 2)
);
