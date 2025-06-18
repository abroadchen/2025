import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

const modulesFn = require.context('./modules', true, /\.js$/);
const regex = /.*\/(.*)\.js$/
console.dir(modulesFn);
const modules = {};

modulesFn.keys().forEach(filepath => {
  console.log(filepath);
  let moduleName = regex.exec(filepath);
  if (moduleName !== null) {
    moduleName = moduleName[1]
  }
  const moduleObj = modulesFn(filepath);
  modules[moduleName] = {
    namespaced: true,
    ...moduleObj.default
  }
})

const initStore = {
    state: {
      loadings: {

      }
    },
    mutations: {

    },
    actions: {
    },
    modules: modules
}

const  tabCount = 20
for (let i = 1; i < tabCount; i++) {
  initStore.state.loadings['tab' + i]  = false
  initStore.mutations['settab' + i] = function ({loadings}, payload) {
    loadings['tab' + i] = payload
  }
}

export default new Vuex.Store(initStore)