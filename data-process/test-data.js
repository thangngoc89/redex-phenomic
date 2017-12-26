const data = require("./packages.json").list;

const packages = [...data];
// Get all keywords
const reducer = (acc, package) => {
  if (package && package.keywords) {
    return [...package.keywords, ...acc];
  }
  return acc;
};
let keywords = packages.reduce(reducer, []);
// unique
keywords = [...new Set(keywords)];
// sort asc
keywords = keywords.sort(sorter);

// turn into a object
let result = {};
for (let i = 0; i < keywords.length; i++) {
  result[keywords[i]] = [];
}

for (let i = 0; i < packages.length; i++) {
  let currentPackage = packages[i];
  let keywordsFromPackage = currentPackage.keywords;
  if (keywordsFromPackage) {
    keywordsFromPackage.forEach(keyword => {
      result[keyword].push(currentPackage);
    });
  }
}

console.log(JSON.stringify(result));

function sorter(a, b) {
  if (!a && !b) return 0;
  if (!a) return -1;
  if (!b) return 1;
  if (b > a) return -1;
  if (a > b) return 1;
  return 0;
}
