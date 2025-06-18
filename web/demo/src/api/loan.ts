
import { request } from '@/utils/request'
import { IResData } from '@/models/ResponseData'
import { AxiosPromise } from 'axios'

interface Pager {
    name: string,
    pageNo: number,
    pageSize: number
}


export const queryLoanList = (pager: Pager): AxiosPromise<IResData<any>> => {
    return request({
        url: '/loan/list',
        method: 'get',
        params: pager
    })
}