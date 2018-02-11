/* resolvers go here, then are linked into a ResolversMap in `js/resolvers.js` */
/* TODO: add types for resolver arguments */
let posts: (unit, unit, Context.t) => Js.Promise.t(list(Schema.Post.t)) =
  (_, _, ctx) =>
    /* statically-typed context! */
    ctx.postsRepo.getPosts();