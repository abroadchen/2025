
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
    Object.defineProperty(obj, attr, {
      get() {
        return value
      },
      set: (newValue) => {
        if (newValue !== value) {
          this.observe(newValue)
          value = newValue
        }
      }
    })
  }
}