const p1 = new Promise((resolve, reject) => {
  resolve('success')
  reject('error')
})

p1.then((data) => {
  console.log(data)
}, e => {
  console.log(e)
})