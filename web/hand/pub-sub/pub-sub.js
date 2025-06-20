class PubSub {

  constructor() {
    this.callback = []
  }

  tap(name, fn) {
    this.callback.push(fn)
  }

  call(...msg) {
    this.callback.forEach(fn => fn(...msg))
  }
}

const ps = new PubSub()
ps.tap('hello', (...msg) => {
  console.log('hello', ...msg)
})

ps.call('hello', 'world')