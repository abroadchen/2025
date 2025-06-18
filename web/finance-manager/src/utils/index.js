import jwt from 'jsonwebtoken'
import {secure} from '@/conf'
import { request, pretty } from "./request"

export const checkLogin = () => {
    const token = getToken()
    if (!token) return null
    return jwt.decode(token, secure)
}
export const getToken = () => {
    return window.localStorage.getItem('token')
}

export function debounce(func, wait=1000) {
    let timeout
    return function () {
        clearTimeout(timeout)
        timeout = setTimeout(func, wait)
    }
}

export function downloadFileForTag(blobData, fileName) {
    let url = window.URL.createObjectURL(blobData)
    let tagA = document.createElement('a')
    tagA.href = url
    tagA.download = fileName
    tagA.style.display = 'none'
    document.body.appendChild(tagA)
    tagA.click()
    document.body.removeChild(tagA)
    window.URL.revokeObjectURL(url)
}

export async function downloadFile(url, fileName) {
    try {
        var res = await request({
            url,
            responseType: 'blob'
        })
        downloadFileForTag(res.data, fileName)
    } catch (e) {
        console.log('下载异常', e)
    }
}