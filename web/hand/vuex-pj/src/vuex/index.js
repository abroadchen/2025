import { forEachValue } from "@/vuex/utils"
import ModuleCollection from "@/vuex/moduleCollection"
import { get } from "core-js/core/dict"
let Vue
const install = (_Vue, options) => {
  Vue = _Vue
  Vue.mixin({
    beforeCreate() {
      if (this.$options.store) {
        this.$store = this.$options.store
      } else {
        if (this.$options.parent && this.$options.parent.$store) {
          this.$store = this.$options.parent.$store
        }
      }
    }
  })
}

function getState(store, path) {
  return path.reduce((newState, key) => {
    return newState[key]
  }, store.state)
}



const installModule = (store, rootState, path, module) => {
  let namespace = store.modules.getNamespace(path)
  if (path.length > 0) {
    let parent = path.slice(0, -1).reduce((m ,v) => {
        return m[v]
      }, rootState)
      Vue.set(parent, path[path.length - 1], module.state)
  }
  module.forEachAction((action, key) => {
    store._actions[namespace + key] = (store._actions[namespace + key] || [])
    store._actions[namespace + key].push((payload) => {
      action.call(store, store, payload)
    })
  })
  module.forEachMutation((mutation, key) => {
    store._mutations[namespace + key] = (store._mutations[namespace + key] || [])
    store._mutations[namespace + key].push((payload) => {
      mutation.call(store, getState(store, path), payload)
      store._subscribers.forEach((fn) => {
        fn(mutation, store.state)
      })
    })
  })
  module.forEachGetter((getter, key) => {
    store._wrappedGetters[namespace + key] = function () {
      return getter(getState(store, path))
    }
  })
  module.forEachChild((child, key) => {
    installModule(store, rootState, path.concat(key), child)
  })
}

proxyStateAndGetterToVm = (store, state) => { 
  const computed = {}
  store.getters = {}
  forEachValue(store._wrappedGetters, (fn, key) => {
    computed[key] = () => fn()
    Object.defineProperty(store.getters, key, {
      get: () => store._vm[key]
    })
  })

  store._vm = new Vue({
    data: {
      $$state: state
    },
    computed
  })
}


class Store {
  constructor(options) {
    const state = options.state
    this.modules = new ModuleCollection(options)
    this._actions = {}
    this._mutations = {}
    this._wrappedGetters = {}
    this._subscribers = []

    installModule(this, state, [], this.modules.root)


    proxyStateAndGetterToVm(this, state)


    options.plugins.forEach(plugin => plugin(this))




    // let state = options.state

    // this.getters = {}
    // const computed = {}
    // // Object.keys(options.getters).forEach(key => {
    // //   computed[key] = () => options.getters[key](this.state)
    // //   Object.defineProperty(this.getters, key, {
    // //     get: () => this._vm[key]
    // //   })
    // // })
    // forEachValue(options.getters, (fn, key) => { 
    //   computed[key] = () => fn(this.state)
    //   Object.defineProperty(this.getters, key, {
    //     get: () => this._vm[key]
    //   })
    // })

    // this._vm = new Vue({
    //   data: {
    //     $$state: state
    //   },
    //   computed
    // })

    // this.mutations = {}
    // // Object.keys(options.mutations).forEach(key => {
    // //   this.mutations[key] = (payload) => options.mutations[key](this.state, payload)
    // // })
    // forEachValue(options.mutations, (fn, key) => {
    //   this.mutations[key] = (payload) => fn(this, payload)
    // })

    // this.actions = {}
    // // Object.keys(options.actions).forEach(key => {
    // //   this.actions[key] = (payload) => options.actions[key](this, payload)
    // // })
    // forEachValue(options.actions, (fn, key) => {
    //   this.actions[key] = (payload) => fn(this, payload)
    // })

  }

  subscribe(fn) {
    this._subscribers.push(fn)
  }

  replaceState(state) {
    this._vm._data.$$state = state
  }

  commit = (type, payload) => {
    // this.mutations[type](payload)
    this._mutations[type].forEach(mutation => mutation.call(this, payload))
  }

  dispatch = (type, payload) => {
    // this.actions[type](payload)
    this._actions[type].forEach(action => action.call(this, payload))
  }

  // get state() {
  //   return this._vm._data.$$state
  // }
}

export function mapState(stateKeyArr) {
  let obj = {}
  for (let i = 0; i < stateKeyArr.length; i++) {
    let key = stateKeyArr[i]
    obj[key] = function () {
      return this.$store.state[key]
    }
  }
  return obj
}

export function mapGetters(stateKeyArr) {
  let obj = {}
  for (let i = 0; i < stateKeyArr.length; i++) {
    let key = stateKeyArr[i]
    obj[key] = function () {
      return this.$store.getters[key]
    }
  }
  return obj
}




export default {
  install,
  Store,
  mapState,
  mapGetters
}