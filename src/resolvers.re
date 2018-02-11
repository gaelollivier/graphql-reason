let posts: (unit, unit, Context.t) => Js.Promise.t(list(Schema.Post.t)) =
  (_, _, ctx) => ctx.postsRepo();