import {Loading, Message, Notification} from 'element-ui';
import Axios from 'axios';
import router from "../router";
import store from '../store'
export const request = Axios.create({
    baseURL: "/api"
});

let loadingInstance;
Axios.interceptors.request.use(config => {
    if (config.loadingTag)
    store.commit(`set${config.loadingTag}`, true)
    const token = window.sessionStorage.getItem('token');
    loadingInstance = Loading.service({fullscreen: true});
    if (token) {
        config.headers.token = token;
    }
    return config;
}, err => {
    return Promise.reject(err);
})
Axios.interceptors.response.use((response) => {
    if (response.config.loadingTag)
    store.commit(`set${response.config.loadingTag}`, false)
    loadingInstance.close();
    const token = response?.data?.data?.token;
    console.log(response);
    if (token) {
        window.sessionStorage.setItem('token', token);
    }
    if (response?.data?.code === 20000) {
        if (typeof response?.data?.data === 'string')
            Message.success(response?.data?.data)
        if (typeof response?.data.data?.info ===  'string')
            Message.success(response?.data.data?.info)
    } else if (response?.data?.code === 603) {
        Notification.error({
            title: '错误',
            message: 'token失效,请重新登录',
        })
        router.replace('/401')
    } else {
        Notification.error({
            title: '错误',
            message: '响应错误'
        })
    }
    return response;
}, err => {
    Message.error(err.message);
    return Promise.reject(err);
})

export const pretty = function (promise) {
    return promise.then(data => [data, undefined])
        .catch(err => [undefined, err])
}