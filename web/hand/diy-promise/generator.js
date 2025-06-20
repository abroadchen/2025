const fs = require('fs')

function read(path) {
  return new Promise((resolve, reject) => {
    fs.readFile(path, 'utf-8', (err, data) => {
      if (err) reject(err)
      resolve(data)
    })
  })
}

function* run() {
  let a = yield read('./a.txt')
  let b = yield read('./b.txt')
  let c = yield read('./c.txt')
  return a + b + c
}

// const it = run()
// it.next().value.then(data => {
//   it.next(data).value.then(data => {
//     it.next(data).value.then(data => {
//       it.next(data)
//     })
//   })
// })

co(run).then(data => { })


async function run() {
  let a = await read('./a.txt')
  let b = await read('./b.txt')
  let c = await read('./c.txt')
  console.log(a, b, c)
}
run()


function main() {

  return co(function* () {
    let a = yield read('./a.txt')
    let b = yield read('./b.txt')
    let c = yield read('./c.txt')
    return { a, b, c }
  })
}

main().then(data => {
  console.log(data)
})