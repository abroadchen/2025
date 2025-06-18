import {request, pretty} from "@/utils/request";

export default {
    methods: {
        beforeInit() { return false },
        afterInit(res) {},
        async init() {
            if (!await this.beforeInit()) { return }
            let [res, err] = await pretty(request({
                url: this.url,
                ...this.customField,
                params: {
                    ...this.getApiPager(),
                    ...this.params
                }
            }))
            this.afterInit(res)
            if (err) return this.$message('请求失败')
            this.tableData = res?.data?.data?.data?.data
            this.setTotal(res?.data?.data?.rows)
        }
    }
}