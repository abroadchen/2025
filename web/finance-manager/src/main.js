import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'

import ElementUI from 'element-ui'
import 'element-ui/lib/theme-chalk/index.css'

Vue.use(ElementUI);

import './assets/normalize.css'
import Axios from 'axios'
//Axios.defaults.baseURL = '/api'
import directives from "./directives"
Vue.use(directives)
import plugins from '@/plugins'
Vue.use(plugins)
import common from "@/common"
Vue.use(common)
import filters from "@/filters"
Vue.use(filters)

Vue.prototype.$ajax = Axios;

Vue.config.productionTip = false

new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')
