import GAsideMenu from "@/components/GAsideMenu"
import GBreadcrumb from "@/components/GBreadcrumb"
import GDropdown from '@/components/GDropdown'
import GFormCreator from "@/components/GFormCreator"
import GTable from "@/components/GTable"
import GColumn from "@/components/GColumn"
// import {Plugin} from 'vue-fragment'
import GSearchQuery from "@/components/GSearchQuery"
function install(Vue) {

    Vue.component(GAsideMenu.name, GAsideMenu);
    Vue.component(GBreadcrumb.name, GBreadcrumb);
    Vue.component(GDropdown.name, GDropdown);
    Vue.component(GFormCreator.name, GFormCreator);
    Vue.component(GTable.name, GTable);
    Vue.component(GColumn.name, GColumn);
    Vue.component(GSearchQuery.name, GSearchQuery);
    // Vue.use(Plugin)
}

export default {
    install
}