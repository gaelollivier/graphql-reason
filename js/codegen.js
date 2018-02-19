import { parse } from 'graphql';
import invariant from 'invariant';

export function generateReasonSchema(typedefs) {
  const schema = parse(typedefs);
  const types = schema.definitions.map(def => {
    invariant(
      def.kind === 'ObjectTypeDefinition',
      'unsuported top level definition of kind: %s',
      def.kind,
    );
    return {
      name: typeName(def.name.value),
      fields: def.fields.map(field => ({
        name: field.name.value,
        type: fieldType(field),
      })),
    };
  });
  const typesDeclaration =
    'type ' +
    types
      .map(
        type =>
          `${type.name} = {\n${type.fields
            .map(field => ` ${field.name}: ${fieldTypeDeclaration(field.type)}`)
            .join(',\n')}\n}`,
      )
      .join('\nand ');
  const toJsHelpers =
    'let ' +
    types
      .map(
        type =>
          `${type.name}ToJs = (${type.name}: ${
            type.name
          }) => {\n${type.fields
            .map(field => ` "${field.name}": ${fieldToJs(type, field)}`)
            .join(',\n')}\n}`,
      )
      .join('\nand ');
  console.log(typesDeclaration);
  console.log(toJsHelpers);
}

// GraphQL -> Reason type name
// -> 1st letter to lowercase
function typeName(schemaType) {
  return schemaType.substr(0, 1).toLowerCase() + schemaType.substr(1);
}

function fieldType(field, props = {}) {
  const kind = field.type.kind;
  switch (kind) {
    case 'NamedType': {
      // regular types are optional by default
      const name = typeName(field.type.name.value);
      return { ...props, name };
    }
    case 'ListType': {
      return fieldType(field.type, { ...props, list: true });
    }
    case 'NonNullType':
      if (props.list) {
        return fieldType(field.type, { ...props, nonNullItems: true });
      } else {
        return fieldType(field.type, { ...props, nonNull: true });
      }
    default:
      throw Error(`unsuported field kind: ${field.type.kind}`);
  }
}

function fieldTypeDeclaration(fieldType) {
  let decl = fieldType.name;
  if (fieldType.list) {
    if (!fieldType.nonNullItems) {
      decl = `option(${decl})`;
    }
    decl = `list(${decl})`;
  }
  if (!fieldType.nonNull) {
    decl = `option(${decl})`;
  }
  return decl;
}

function fieldToJs(parentType, field) {
  let toJs = `${parentType.name}.${field.name}`;
  if (!field.type.nonNull) {
    toJs += `${toJs} |> optionToJs(${toJsFunc(field)})`;
  } else if (field.type.list) {
    toJs += `${toJs} |> ${toJsFunc(field)}`;
  }
  return toJs;
}

function isScalar(type) {
  return ['int', 'float', 'string', 'boolean'].includes(type);
}

function toJsFunc(field) {
  let fnName = isScalar(field.type.name) ? 'scalar' : field.type.name;
  if (field.type.list) {
    if (!field.type.nonNullItems) {
      fnName += 'Option';
    }
    fnName += 'List';
  }
  return fnName + 'ToJs';
}
