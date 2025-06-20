import Vue from 'vue'
import Vuex from 'vuex'

// import logger from 'vuex/dist/logger'
import Vuex from '@/vuex'
function persists() {
  return function (store) {

    let data = localStorage.getItem('VUEX:STATE')

    if (data) {
      store.replaceState(JSON.parse(data))
    }

    store.subscribe((mutation, state) => {
      localStorage.setItem('VUEX:STATE', JSON.stringify(state))
    })
  }
}



Vue.use(Vuex)


const store = new Vuex.Store({
  plugins: [
    // logger(),
    persists()
  ],
  state: {
    count: 0
  },
  getters: {//computed 过滤处理
    doubleCount: state => state.count * 2
  },
  mutations: {//同步$store.commit('方法名',payload)
    increment(state) {
      state.count++
    }
  },
  actions: {//异步$store.dispatch()
    increment: ({ commit }) => commit('increment')
  }
})

export default store