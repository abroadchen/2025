
class Observe {
  constructor(obj) {
    this.observe(obj)
  }
  observe(obj) {
    if (obj && typeof obj === 'object') {
      for (let attr in obj) {
        this.defineReactive(obj, attr, obj[attr])
      }
    }
  }
  defineReactive(obj, attr, value) {
    this.observe(value)
    let dep = new Dep()
    Object.defineProperty(obj, attr, {
      get() {
        Dep.target && dep.addSub(Dep.target)
        return value
      },
      set: (newValue) => {
        if (newValue !== value) {
          this.observe(newValue)
          value = newValue
          dep.notify()
        }
      }
    })
  }
}