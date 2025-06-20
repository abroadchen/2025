function myco(generatorFn) {

  const it = generatorFn()

  return new Promise((resolve, reject) => {
    function next(lastValue) {
      let { value, done } = it.next(lastValue)
      if (done) {
        resolve(value)
      } else {
        value.then(next, reject)
      }
    }
    next()
  })
}