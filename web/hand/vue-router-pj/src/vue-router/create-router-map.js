
function createRouteRecord(route, pathMap, parent) {
  let path = parent ? (parent.path + '/' + route.path) : route.path
  let component = route.component

  let record = {
    path,
    component,
    parent
  }

  if (!pathMap[path]) {
    pathMap[path] = record
  }

  if (route.children) {
    route.children.forEach(childRoute => {
      createRouteRecord(childRoute, pathMap, record)
    })
  }
}




export default function createRouteMap(routes, oldPathMap) {
  let pathMap = oldPathMap || {}

  routes.forEach(route => {
    createRouteRecord(route, pathMap)
  })

  return {
    pathMap
  }
}