/*
     reason types from graphql schema
     TODO: automatically generate this from GraphQL schema :)
 */
type user = {
  id: int,
  name: string,
  posts: option(list(option(post))),
  group: option(group)
}
and group = {
  id: int,
  name: string,
  users: list(user)
}
and post = {
  id: int,
  title: string,
  author: user
};

let optionToJs: ('t => 'js, option('t)) => Js.nullable('js) =
  (toJs, optional) =>
    switch optional {
    | None => Js.Nullable.null
    | Some(thing) => Js.Nullable.return(toJs(thing))
    };

let rec userToJs = (user: user) => {
  "id": user.id,
  "name": user.name,
  "posts": user.posts |> optionToJs(postOptionListToJs),
  "group": optionToJs(groupToJs, user.group)
}
and groupToJs = (group: group) => {
  "id": group.id,
  "name": group.name,
  "users": group.users |> List.map(userToJs)
}
and postToJs = (post: post) => {
  "id": post.id,
  "title": post.title,
  "author": userToJs(post.author)
}
and postOptionToJs = (postOption: option(post)) => postOption |> optionToJs(postToJs)
and postOptionListToJs = (postOptionList: list(option(post))) =>
  postOptionList |> List.map(postOptionToJs) |> Array.of_list
and postsToJs = (l) => l |> List.map(postToJs) |> Array.of_list;