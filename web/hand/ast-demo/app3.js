const { parse } = require('@babel/parser')
const generator = require('@babel/generator').default
const traserve = require('@babel/traverse').default

let code = `
let sum = 12 + 66
let c = sum + 100
console.log(sum)
`

const ast = parse(code)

traserve(ast, {
	enter(NodePath) {
		if (NodePath.type === 'Identifier' && NodePath.node.name === 'c') {
			NodePath.parentPath.remove()
		}
	},
	Identifier(NodePath) {
		if (NodePath.node.name === 'c') {
			NodePath.parentPath.remove()
		}
	}
})

let nowCode = generator(ast).code