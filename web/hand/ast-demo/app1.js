const { parse } = require('@babel/parser')
const traverse = require('@babel/traverse').default
const generator = require('@babel/generator').default

let code = `let sum = 12 + 66`

const ast = parse(code)

// console.log(ast)

traverse(ast, {
	enter(NodePath) {},
	exit(NodePath) {},
	Identifier(NodePath) {}
})

let newCode = generator(ast).code