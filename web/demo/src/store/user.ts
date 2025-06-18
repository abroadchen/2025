import { defineStore } from "pinia"

class UserStore {
    // menus: any[] = [];
    menus: Array<any> = [];
    isLogin: boolean = false;
    userInfo: Object = {};
}




export const useUser = defineStore('user', {
    state() {
        // return {
        //     menus: [1],
        //     isLogin: false
        // }
        return new UserStore()
    },
    actions: {
        login() {
            this.isLogin = true
        },
        logout() {
            this.isLogin = false
        },
        setMenus(menus: any[]) {
            this.menus = menus
        },
        setUserInfo(user: any) {
            this.$patch({
                userInfo: user
            })
        }
    }
})