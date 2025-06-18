import jwt from 'jsonwebtoken'
import { secure } from "@/config";

export const getUserInfo = () => {
    const token = window.sessionStorage.getItem('token')
    let userinfo = jwt.decode(token, secure)
    return userinfo
}


export const isLogin = () => {

    return !!getUserInfo()
}