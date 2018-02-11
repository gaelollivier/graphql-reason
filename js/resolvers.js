// wire-up Reason resolvers with js code

// import reason code, relative to build/
import reasonResolvers from '../lib/js/src/resolvers';
import reasonSchema from '../lib/js/src/schema';

// generate a resolver that transforms Reason results
// to JS results (i.e: records to Js.t, lists to arrays, ...)
const generateJsResolver = typeName => {
  const resolver = reasonResolvers[typeName];
  const toJs = reasonSchema[`${typeName}ToJs`];
  return (src, args, ctx) => resolver(src, args, ctx).then(toJs);
};

// Generate resolver map, using Reason resolvers
export default {
  Query: {
    posts: generateJsResolver('posts'),
  },
};
