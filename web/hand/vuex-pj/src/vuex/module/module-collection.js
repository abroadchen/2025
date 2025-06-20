import { forEachValue } from "../utils"
import Module from './module'

export default class ModuleCollection { 
  constructor(options) {
    this.register([], options)
  }

  getNamespace(path) {
    let root = this.root
    return path.reduce((str, key) => {
      root = root.getChild(key)
      return str + (root.namespaced ? key + '/' : '')
    }, '')
  }


  register(path, rootModule) {
    let newModule = new Module(rootModule)
    // let newModule = {
    //   '_raw': rootModule,
    //   '_children': {},
    //   'state': rootModule.state
    // }
    if (path.length === 0) {
      this.root = newModule
    } else {
      let parent = path.slice(0, -1).reduce((m ,v) => {
        return m.getChild(v)
      }, this.root)
      // parent._children[path[path.length - 1]] = newModule
      parent.addChild(path[path.length - 1], newModule)
    }
    if (rootModule.modules) {
      forEachValue(rootModule.modules, (module, moduleName) => {
        this.register(path.concat(moduleName), module)
      })
    }
  }
}