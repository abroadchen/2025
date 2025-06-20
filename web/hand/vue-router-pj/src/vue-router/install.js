
export const install = (Vue, options) => {

  Vue.mixin({
    beforeCreate() {
      if (this.$options.router) {
        this._routerRoot = this
        this._router = this.$options.router
        this._router.init(this)

        Vue.util.defineReactive(this, '_route', this._router.history.current)

      } else {
        this._routerRoot = this.$parent && this.$parent._routerRoot
      }
    }
  })

  Vue.component('router-link', Link)

  Vue.component('router-view', View)

  // Vue.prototype.$route = {}
  // Vue.prototype.$router = {}

  Object.defineProperty(Vue.prototype, '$route', {
    get() {
      return this._routerRoot._route
    }
  })

  Object.defineProperty(Vue.prototype, '$router', {
    get() {
      return this._routerRoot._route
    }
  })
}