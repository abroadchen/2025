export default {
    data() {
        return {
            currentPage: 1,
            pageSizes: [10,20,30,40],
            pageSize: 10,
            total: 0,
            query: ''
        }
    },
    computed: {
        frontPageOptions() {
            return {
                currentPage: this.currentPage,
                pageSize: this.pageSize,
                pageSizes: this.pageSizes,
                query: this.query,
                total: this.total
            }
        }
    },
    methods: {

        getApiPager() {
            let params = {
                pageNo: this.currentPage,
                pageSize: this.pageSize,
            }
            if (this.query && this.query.trim() !== '') {
                params.name = this.query
            }
            return params
        },

        setTotal(total) {
          this.total = total
        },
        setQueryName(q) {
            this.query = q
            this.currentPage = 1
            this.init()
        },
        sizeChange(size) {
            this.pageSize = size
            this.init()
        },

        currentPageChange(page){
            this.currentPage = page
            this.init()
        },
    }
}