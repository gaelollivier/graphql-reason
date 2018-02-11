/*
     reason types from graphql schema
     TODO: automatically generate this from GraphQL schema :)
 */
module Post = {
  [@bs.deriving {jsConverter: newType}]
  type t = {
    id: int,
    title: string
  };
};

let postToJs = Post.tToJs;

let postsToJs: list(Post.t) => array(Post.abs_t) =
  (l) => l |> List.map(Post.tToJs) |> Array.of_list;