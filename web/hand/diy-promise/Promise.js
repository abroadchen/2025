
const PENDING = 'pending'
const SUCCESS = 'fulfilled'
const FAIL = 'rejected'

const resolvePromise = (promise2, x, resolve, reject) => {
  if (promise2 === x) {
    return reject(new TypeError('循环引用'))
  }

  if (typeof x === 'object' && x !== null || typeof x === 'function') {
    let called
    try {
      let then = x.then
      if (typeof then === 'function') {
        then.call(x, y => {
          if (called) return
          called = true
          resolvePromise(promise2, y, resolve, reject)
        }, r => {
          if (called) return
          called = true
          reject(r)
        })
      } else {
        if (called) return
        called = true
        resolve(x)
      }
    } catch (error) {
      if (called) return
      called = true
      reject(error)
    }
  } else {
    resolve(x)
  }
}






class Promise {
  constructor(executor) {
    this.status = PENDING
    this.value = undefined
    this.reason = undefined

    this.onResolvedCallbacks = []
    this.onRejectedCallbacks = []

    const resolve = (value) => {
      if (this.status === PENDING) {
        this.value = value
        this.status = SUCCESS
        this.onResolvedCallbacks.forEach(fn => fn())
      }
    }

    const reject = (reason) => {
      if (this.status === PENDING) {
        this.reason = reason
        this.status = FAIL
        this.onRejectedCallbacks.forEach(fn => fn())
      }
    }

    try {
      executor(resolve, reject)
    } catch (e) {
      reject(e)
    }
  }

  then(onFulfilled, onRejected) {


    onFulfilled = typeof onFulfilled === 'function' ? onFulfilled : value => value
    onRejected = typeof onRejected === 'function' ? onRejected : reason => { throw reason }

    const promise2 = new Promise((resolve, reject) => {
      if (this.status === SUCCESS) {
        setTimeout(() => {
          try {
            let x = onFulfilled(this.value)
            resolvePromise(promise2, x, resolve, reject)
          } catch (e) {
            reject(e)
          }
        }, 0)
      }

      if (this.status === FAIL) {
        setTimeout(() => {
          try {
            let x = onRejected(this.reason)
            resolvePromise(promise2, x, resolve, reject)
          } catch (e) {
            reject(e)
          }
        }, 0)
      }

      if (this.status === PENDING) {
        this.onResolvedCallbacks.push(() => {
          setTimeout(() => {
            try {
              let x = onFulfilled(this.value)
              resolvePromise(promise2, x, resolve, reject)
            } catch (e) {
              reject(e)
            }
          }, 0)
        })
        this.onRejectedCallbacks.push(() => {
          setTimeout(() => {
            try {
              let x = onRejected(this.reason)
              resolvePromise(promise2, x, resolve, reject)
            } catch (e) {
              reject(e)
            }
          }, 0)
        })
      }
    })

    return promise2


  }

  static resolve(val) {
    if (val instanceof Promise) return val
    return new Promise(resolve => resolve(val))
  }

  static reject(reason) {
    return new Promise((resolve, reject) => reject(reason))
  }

  static all(arr) {
    return new Promise((resolve, reject) => {
      let rs = []
      let index = 0
      for (let i = 0; i < arr.length; i++) {
        let current = arr[i]
        if (current instanceof Promise) {
          current.then((data) => {
            rs[i] = data
            index++
            if (index === arr.length) resolve(rs)
          }, reject)
        } else {
          rs[i] = current
          index++
          if (index === arr.length) resolve(rs)
        }
      }
    })
  }

  static race(arr) {
    return new Promise((resolve, reject) => {
      for (let i = 0; i < arr.length; i++) {
        let current = arr[i]
        if (current instanceof Promise) {
          current.then(resolve, reject)
        } else {
          resolve(current)
        }
      }
    })
  }

  finally(cb) {
    return this.then((data) => {
      cb()
      return data
    }, (err) => {
      cb()
      throw err
    })
  }
}


Promise.defer = Promise.deferred = () => {
  const df = {}
  df.promise = new Promise((resolve, reject) => {
    df.resolve = resolve
    df.reject = reject
  })
  return df
}





module.exports = Promise