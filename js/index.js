import { importSchema } from 'graphql-import';
import { makeExecutableSchema } from 'graphql-tools';

import express from 'express';
import expressGraphQL from 'express-graphql';
import logger from 'morgan';

import resolvers from './resolvers';
import context from './context';

console.log('Initializing schema...');

// load schema files (relative to build/index.js)
const typeDefs = importSchema(__dirname + '/../schema/schema.graphql');

import { generateReasonSchema } from './codegen';

generateReasonSchema(typeDefs);

const schema = makeExecutableSchema({
  typeDefs,
  resolvers,
  logger: { log: event => console.error('Error:', event) },
});

// setup web server
const port = process.env.PORT || 7000;

const app = express();

// setup middlewares
app.use(logger('dev'));

app.use(
  '/graphql',
  expressGraphQL(request => ({
    schema,
    context: context(request),
  })),
);

app.listen(port);
console.log(`Listening on port ${port}`);
