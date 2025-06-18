import  axios, {AxiosResponse}  from "axios";
import { IResData } from "@/models/ResponseData";

export const request = axios.create({
    baseURL: '/api',
    // timeout: 5000
})

interface Test {
    // token: string
    [k:string]:any;
}

request.interceptors.request.use(config => {
    const token = window.sessionStorage.getItem('token')
    if (token) {
        // config.headers.Authorization = `Bearer ${token}`
        (config.headers as any).token = token
    }
    return config
}, error => {
    return Promise.reject(error)
})

request.interceptors.response.use((response: AxiosResponse<IResData>) => {
    const token = response.data.data.token
    if (token) {
        window.sessionStorage.setItem('token', token)
    }
    return response
}, error => {
    return Promise.reject(error)
})