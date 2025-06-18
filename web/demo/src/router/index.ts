import { createRouter, createWebHashHistory, RouteRecordRaw } from 'vue-router'
import HomeView from '../views/HomeView.vue'
import { whiteList } from '@/config'
import { isLogin } from "@/utils"
import { useUser } from "@/store/user"
import  axios  from 'axios'
import Layout from '../layouts/index.vue'
import component from "*.vue";

const routes: Array<RouteRecordRaw> = [
  {
    path: '/',
    redirect: '/home'
  },
  {
    path: '/',
    name: 'home',
    component: Layout,
    children: [
      { path:'/home', component: HomeView }
    ]
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
    path: '/404',
    component: () => import('../views/NotFound.vue')
  },
  {
    path: '/login',
    name: 'Login',
    // route level code-splitting
    // this generates a separate chunk (about.[hash].js) for this route
    // which is lazy-loaded when the route is visited.
    component: () => import(/* webpackChunkName: "about" */ '../views/Login.vue')
  }

]

const router = createRouter({
  history: createWebHashHistory(),
  routes
})

const modules = (import.meta as any).glob('../views/**/*.vue')

function asyncRoutesHandler(routes: any[]) {
  return routes.map((route: any) => {
    if (route.component === 'Layout') {
      route.component = Layout
    } else {
      const compPath = route.component
      // route.component = () => import(`../views/${compPath}.vue`)
      route.component = modules[`../views/${compPath}.vue`]
    }
    if (route.children) {
      route.children = asyncRoutesHandler(route.children)
    }
    return  route
  })
}

async function loadMenus(to: any, next: any) {
  const user = useUser()
  const res = await axios.get('/menus.json')
  const asyncRoutes = asyncRoutesHandler(res.data)
  user.setMenus(res.data)

  asyncRoutes.forEach(r => {
    router.addRoute(r)
  })

  router.addRoute({ path: '/:catchAll(.*)', redirect: '/404'})
  next({...to, replace: true})
}

router.beforeEach((to, from, next) => {
  const user = useUser()
  if (whiteList.includes(to.path)) {
    return  next()
  }

  if (!isLogin()) {
    return next('/login?redirecet=' + to.path)
  }

  if (user.menus.length === 0) {
    return loadMenus(to, next)
  }
  next()
})

export default router
