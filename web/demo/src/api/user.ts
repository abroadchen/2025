
import { request } from '@/utils/request'
import { IUser, ILoginData } from '@/models/User'
import { IResData } from '@/models/ResponseData'
import { AxiosPromise } from 'axios'
export const doLogin = (user: IUser): AxiosPromise<IResData<ILoginData>> => {
    return request({
        url: '/user/login',
        method: 'post',
        data: user
    })
}