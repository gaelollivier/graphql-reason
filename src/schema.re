type t;

type schemaConfig;

[@bs.obj]
external makeConfig :
  (~query: ObjectType.t, ~mutation: option(ObjectType.t)=?, unit) => schemaConfig =
  "";

[@bs.new] [@bs.module "graphql"] external createWithConfig : schemaConfig => t = "GraphQLSchema";

let create = (~query: ObjectType.t, ~mutation: option(ObjectType.t)=?, ()) =>
  createWithConfig(makeConfig(~query, ~mutation, ()));