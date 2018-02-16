/* example repository */
type t = {getPosts: unit => Js.Promise.t(list(Schema.post))};

let getPosts = () => {
  let userGroup: Schema.group = {id: 84, name: "MyGroup", users: []};
  let user: Schema.user = {id: 42, name: "Bob", posts: Some([]), group: Some(userGroup)};
  let posts = [Schema.{id: 1, title: "My article", author: user}];
  Js.log(Schema.postsToJs(posts));
  Js.Promise.resolve(posts)
};

let create = () => {getPosts: getPosts};