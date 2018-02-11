/* example repository */
type t = {getPosts: unit => Js.Promise.t(list(Schema.Post.t))};

let getPosts = () =>
  Js.Promise.resolve([
    Schema.Post.{id: 1, title: "Hello world!"},
    Schema.Post.{id: 2, title: "Reason rocks!"}
  ]);

let create = () => {getPosts: getPosts};