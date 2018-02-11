type t = {
  /* context will hold repositories */
  postsRepo: unit => Js.Promise.t(list(Schema.Post.t))
};

let createContext: unit => t =
  () => {
    /* will create context from request */
    postsRepo: () => Js.Promise.resolve([Schema.Post.{id: 42, title: "Hello world!"}])
  };