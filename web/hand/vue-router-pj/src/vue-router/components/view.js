export default {

  functional: true,
  render(h, { parent,data }) {

    let route = parent.$route

    let deepth = 0
    data.routerView = true
    while (parent) {
      if (parent.$vnode && parent.$vnode.data.routerView) {
        deepth++
      }
      parent = parent.$parent
    }

    let record = route.matched[deepth]
    if (!record) {
      return h()
    }

    return h(record.component,data)
  }
}