import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import '@/assets/index.css'
import { createPinia } from 'pinia'
import GAsideMenu from "@/components/GAsideMenu.vue";
import GBreadcrumb from "@/components/GBreadcrumb.vue";

const app = createApp(App)
app.config.globalProperties.$abc = '123'
declare module '@vue/runtime-core' {
    interface ComponentCustomProperties {
        $route: any;
        $router: any;
        $abc: any;
    }
}
app.component('GAsideMenu', GAsideMenu)
app.component(GBreadcrumb.name, GBreadcrumb)

createApp(App).use(createPinia()).use(ElementPlus).use(router).mount('#app')
