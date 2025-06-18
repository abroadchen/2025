import Vue from 'vue'
import VueRouter from 'vue-router'
import HomeView from '../views/HomeView.vue'
import {whiteUrlList} from "@/conf"
import {checkLogin} from '@/utils'
import store from '@/store'
import Axios from 'axios'
import {pretty} from "@/utils/request"
import Layout from '@/layouts/Layout'
import Router from "@vue/cli-plugin-router/generator/template/src/router";

Vue.use(VueRouter)

const routerPush = Router.prototype.push
Router.prototype.push = function push(location) {
  return routerPush.call(this, location).catch(error => error)
}


const constantRoutes = [
  {
    path: '/',
    redirect: '/home',
    name: 'Home',
    meta: {
      title: '首页',
    },
    component: Layout,
    children: [
      {
        path: '/home',
        component: HomeView,
      }
    ]
  },
  {
    path: '/404',
    name: 'NotFound',
    component: () => import('../views/404.vue'),
  },
  {
    path: '/401',
    name: 'Reject',
    component: () => import('../views/401.vue'),
  },
  {
    path: '/about',
    name: 'about',
    // route level code-splitting
    // this generates a separate chunk (about.[hash].js) for this route
    // which is lazy-loaded when the route is visited.
    component: () => import(/* webpackChunkName: "about" */ '../views/AboutView.vue')
  },
  {
    path: '/login',
    name: 'Login',
    // route level code-splitting
    // this generates a separate chunk (about.[hash].js) for this route
    // which is lazy-loaded when the route is visited.
    component: () => import(/* webpackChunkName: "about" */ '../views/Login.vue')
  },
  // {
  //   path: '*',
  //   redirect: {name: 'NotFound'}
  // }
]

const router = new VueRouter({
  routes: constantRoutes
})

function asyncRoutesHandler(routes) {
  return routes.map(r => {
    if (r.component === 'Layout') {
      r.component = Layout
    } else {
      const filepath = r.component
      r.component = () => import((`../views/${filepath}.vue`))
    }
    if (r.children) {
      r.children = asyncRoutesHandler(r.children)
    }
    return r
  })
}



async function loadMenus(next, to) {
  let [res, err] = await pretty(Axios.get('/menus.json', {
    responseType: "json"
  }))
  if (err) {
    throw new Error('加载动态菜单错误' + err.message)
  }
  let asyncRoutes = asyncRoutesHandler(res.data)
  asyncRoutes.push({
    path: '*',
    redirect: {name: 'NotFound'}
  })
  asyncRoutes.forEach(r => {
    router.addRoute(r)
  })
  store.commit('user/changeUserMenus', res.data)
  next({...to, replace: true})
}



router.beforeEach((to, from, next) => {
  if (whiteUrlList.includes(to.path)) {
    return next()
  }
  let userInfo = checkLogin()
  if (userInfo) {
    if (!store.getters['user/getUserInfo']) {
      store.commit('user/changeUserInfo', {
        username: userInfo.account
      })
      store.commit('user/changeIsLogin', true)
    }
    if (!store.getters['user/getUserMenus']) {
      return loadMenus(next, to)
    } else {
      if (to.name)
      store.commit('user/addTag', {
        title: to?.meta?.title,
        compName: to.name
      })
      return next()
    }
  } else {
    next('/login?redirect=' + to.path)
  }
})


export default router
