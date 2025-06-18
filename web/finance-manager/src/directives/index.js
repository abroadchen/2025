
import dragTable from './drapTable'
function install(Vue) {
    Vue.directive(dragTable.name, dragTable.handler)
}

export default { install}