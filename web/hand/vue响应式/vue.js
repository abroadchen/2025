class Vue {
  constructor(options) {
    if (this.isElement(options.el)) {
      this.$el = options.el
    } else {
      this.$el = document.querySelector(options.el)
    }
    this.$data = options.data
    this.proxyDataToVm()
    this.$computed = options.computed
    this.computedToData()
    this.$methods = options.methods
    new Observer(this.$data)
    new Compiler(this)
  }

  computedToData() {
    for (let attr in this.$computed) {
      Object.defineProperty(this.$data, attr, {
        get: () => {
          return this.$computed[attr].call(this)
        }
      })
    }
  }



  proxyDataToVm() {
    for (let attr in this.$data) {
      Object.defineProperty(this, attr, {
        get: () => {
          return this.$data[attr]
        }
      })
    }
  }



  isElement(node) {
    return node && node.nodeType === 1
  }
}

const DirectiveUtils = {
  getValue(vm, value) {
    return value.split('.').reduce((data, key) => {
      return data[key.trim()]
    }, vm.$data)
  },
  setValue(vm, value, newValue) {
    value.split('.').reduce((data, k, index, arr) => {
      if (index == arr.length - 1) {
        data[k] = newValue
      }
      return data[k]
    })
  },
  getContent(vm, value) {
    let reg = /\{\{(.+?)\}\}/ig
    return value.replace(reg, (...args) => {
      return this.getValue(vm, args[1])
    })
  },
  model(node, value, vm) {
    new Watcher(vm, value, (newValue, oldValue) => {
      node.value = newValue
    })
    node.value = this.getValue(vm, value)
    node.addEventListener('input', (e) => {
      let newValue = e.target.value
      this.setValue(vm, value, newValue)
    })
  },
  html(node, value, vm) {
    new Watcher(vm, value, (newValue, oldValue) => {
      node.value = newValue
    })
    node.innerHTML = this.getValue(vm, value)
  },
  text(node, value, vm) {
    new Watcher(vm, value, (newValue, oldValue) => {
      node.value = newValue
    })
    node.innerText = this.getValue(vm, value)
  },
  content(node, content, vm) {
    let reg = /\{\{(.+?)\}\}/ig
    let val = this.content.replace(reg, (...args) => {
      new Watcher(vm, args[1], (newValue, oldValue) => {
        node.textContent = this.getContent(vm, content)
      })
      return this.getValue(vm, args[1])
    })
    node.textContent = val
  },
  on(node, value, vm, type) {
    node.addEventListener(type, (e) => {
      vm.$methods[value].call(vm, e)
    })
  }
}



class Compiler {
  constructor(vm) {
    this.vm = vm
    let fragment = this.nodeToFragment(this.vm.$el)
    this.buildTemplate(fragment)
    this.vm.$el.appendChild(fragment)
  }

  buildTemplate(fragment) {
    let nodeList = [...fragment.childNodes]
    nodeList.forEach(node => {
      if (this.vm.isElement(node)) {
        this.buildElement(node)
        this.buildTemplate(node)
      } else {
        this.buildText(node)
      }
    })
  }

  buildElement(node) {
    let attrs = [...node.attributes]
    attrs.forEach(attr => {
      let { name, value } = attr
      if (name.startsWith('v-')) {
        let [directiveName, directiveType] = name.split(':')
        let [_, directive] = directiveName.split('-')
        DirectiveUtils[directive](node, value, this.vm, directiveType)
      }
    })
  }

  buildText(node) {
    let content = node.textContent
    let reg = /\{\{.+?\}\}/ig
    if (reg.test(content)) {
      DirectiveUtils['content'](node, content, this.vm)
    }
  }

  nodeToFragment(app) {
    let fragment = document.createDocumentFragment()
    let node = app.firstChild
    while (node) {
      fragment.appendChild(node)
      node = app.firstChild
    }
  }
}


class Watcher {
  constructor(vm, attr, cb) {
    this.vm = vm
    this.attr = attr
    this.cb = cb
    this.oldValue = this.getOldValue()
  }

  getOldValue() {
    Dep.target = this
    let oldValue = DirectiveUtils.getValue(this.vm, this.attr)
    Dep.target = null
    return oldValue
  }

  update() {
    let newValue = DirectiveUtils.getValue(this.vm, this.attr)
    if (newValue !== this.oldValue) {
      this.cb(newValue, this.oldValue)
    }
  }
}


class Dep {
  constructor() {
    this.subs = []
  }

  addSub(watcher) {
    this.subs.push(watcher)
  }

  notify() {
    this.subs.forEach(watcher => watcher.update())
  }
}