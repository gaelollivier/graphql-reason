/*
   context is statically-typed thanks to Reason
   a single `createContext` function is exposed via `js/context.js`
 */
type t = {
  /*
     context holds repositories, along with any request-scoped
     information (ie: auth info, data loaders, ...)
   */
  postsRepo: PostsRepository.t
};

let createContext: unit => t =
  /* create context from request (not passed yet) */
  (_request) => {
    /* create posts repository */
    postsRepo: PostsRepository.create()
  };