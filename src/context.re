/*
   context is statically-typed thanks to Reason
   a single `createContext` function is exposed
   via `js/context.js`
 */
type t = {
  /* context will hold repositories */
  postsRepo: unit => Js.Promise.t(list(Schema.Post.t))
};

let createContext: unit => t =
  /* create context from request */
  (_request) => {
    /* dummy posts repository */
    postsRepo: () =>
      Js.Promise.resolve([
        Schema.Post.{id: 1, title: "Hello world!"},
        Schema.Post.{id: 2, title: "Reason rocks!"}
      ])
  };