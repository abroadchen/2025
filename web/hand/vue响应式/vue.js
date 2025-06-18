class Vue {
  constructor(options) {
    if (this.isElement(options.el)) {
      this.$el = options.el
    } else {
      this.$el = document.querySelector(options.el)
    }
    this.$data = options.data
    new Compiler(this)
  }
  isElement(node) {
    return node && node.nodeType === 1
  }
}

const DirectiveUtils = {
  getValue(vm, value) {
    return value.split('.').reduce((data, key) => {
      return data[key]
    }, vm.$data)
  },
  model(node, value, vm) {
    node.value = this.getValue(vm, value)
  },
  html(node, value, vm) {
    node.innerHTML = this.getValue(vm, value)
  },
  text(node, value, vm) {
    node.innerText = this.getValue(vm, value)
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
        let [_, directive] = name.split('-')
        DirectiveUtils[directive](node, value, this.vm)
      }
    })
  }

  buildText(node) {
    let content = node.textContent
    let reg = /\{\{.+?\}\}/ig
    if (reg.test(content)) { }
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