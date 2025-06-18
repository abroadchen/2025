import {logout} from "@/apis/user"
import {Message} from 'element-ui'
export default {
    state: {
        isLogin: false,
        userInfo: null,
        userMenus: null,
        cachedTags: [{
            title: '测试导航',
            compName: []
        }]
    },
    getters: {

        getIsLogin: state => {
            return state.isLogin
        },
        getUserInfo: state => {
            return state.userInfo
        },
        getUserMenus: state => {
            return state.userMenus
        },
        getTags(state) {
            return state.cachedTags
        }
    },
    mutations: {
        delTag(state, tag) {
            let index = state.cachedTags.findIndex(t=>{
                return tag.compName === t.compName
            })
            if (!index !== -1) {
                state.cachedTags.splice(index, 1)
            }
        },
        addTag(state, tag) {
            let findTag = state.cachedTags.find(t=>{
                return tag.compName === t.compName
            })
            if (!findTag) {
                state.cachedTags.push(tag)
            }
        },
        changeIsLogin: (state, payload) => {
            state.isLogin = payload
        },
        changeUserInfo: (state, payload) => {
            state.userInfo = payload
        },
        changeUserMenus: (state, payload) => {
            state.userMenus = payload
        }
    },
    actions: {
        async doLogout({commit, dispatch}, payload) {
            let [res, err] = await logout()
            if (err) {
                return Message.error('退出失败!')
            }
            commit('changeIsLogin', false)
            commit('changeUserInfo', null)
            commit('changeUserMenus', null)
            window.sessionStorage.setItem('token', '')
        }
    }
}