const t = require('@babel/types')
const { parse } = require('@babel/parser')
const generator = require('@babel/generator').default

let left = t.numericLiteral(12)
let right = t.numericLiteral(66)

let init = t.binaryExpression('+', left, right)

let id = t.identifier('sum')

let vd = t.variableDeclarator(id, init)

let vds = t.variableDeclaration('let', [vd])

let code = ''

const ast = parse(code)
ast.program.body.push(vds)

code = generator(ast).code