type package = {
  .
  "_type": string,
  "description": string,
  "id": string,
  "keywords": array(string),
  "license": Js.nullable(string),
  "maintenance": float,
  "name": string,
  "popularity": float,
  "quality": float,
  "slug": string,
  "score": float,
  "stars": Js.nullable(string),
  "updated": Js.Date.t,
  "version": string,
  "body": string,
  "homepageUrl": Js.nullable(string),
  "repositoryUrl": Js.nullable(string),
  "npmUrl": Js.nullable(string),
  "issuesUrl": Js.nullable(string),
  "docsUrl": Js.nullable(string)
};

type keywords = {
  .
  "name": string,
  "count": int
};