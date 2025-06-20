const { parse } = require('@babel/parser')

let code = `let sum = 12 + 66`

const ast = parse(code)

console.log(ast)
