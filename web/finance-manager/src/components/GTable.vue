<script>
export default {
  name: 'GTable',
  render() {
    const {g_pageOptions, showPagination} = this
    return (
      <div >
        {this.renderTable()}
        { showPagination && this.renderPagination(g_pageOptions)}
      </div>
    )
  },
  methods: {


    renderIndex() {
      return <el-table-column align="center" label="序号" type="index" width="55"></el-table-column>
    },
    renderMultiSelect() {
      return <el-table-column
          reserve-selection={true}
          type="selection" width="55"></el-table-column>
    },
    renderTable() {
      const {columns, loadingTag, g_options, data, $store:{state: {loadings}}} = this
      const directives = [
        {
          name: 'loading',
          modifiers: {
            gwapper: true
          },
          value: loadings[loadingTag]
        },
        {
          name: 'drag'
        }
      ]
      let {useIndex} = g_options
      let {useMultiSelect} = g_options
      return (
            <el-table id="gwapper"
                      onSelection-change={e => this.$emit('selection-change', e)}
                      {...{directives}}
                      data={data} attrs={g_options}>
              { useIndex && this.renderIndex()}
              { useMultiSelect && this.renderMultiSelect()}
              {/*this.renderTableColumns(columns)*/}
              {/*<GColumn scopedSlots={this.$scopedSlots} column={columns}></GColumn>*/}

                import GColumn from "@/components/GColumn.vue";
              {
                columns && columns.map((col,i) => {
                  return <GColumn key={i} column={col} scopedSlots={this.$scopedSlots}/>
                  })
              }
            </el-table>
      )
    },
    handleCurrentChange(page) {
      this.$emit('handleCurrentChange', page)
    },
    renderPagination(options) {
      return (
          <el-pagination onSize-change={e=>this.$emit('size-change', e)}
    onCurrent-change={this.handleCurrentChange}
     attrs={options}
      layout="total, sizes, prev, pager, next, jumper"
    ></el-pagination>
      )
    }
  },
  computed: {
    //监视外部属性的改变 合并本来的配置
    g_options() {
      return Object.assign({}, this.gOptions, this.options)
    },
    g_pageOptions() {
      return Object.assign({}, this.gPageOptions, this.pageOptions)
    }
  },
  data() {
    return {
      gOptions: {
        stripe: true,
        border: false,
        fit: true,
        showHeader: true,
        rowKey: 'id',
        useMultiSelect: false,
        useIndex: true
      },
      gPageOptions: {
        currentPage: 1,
        pageSizes: [100,200,300,400],
    pageSize: 100,
    total: 400
  }
    }
  },
  props: {
    showPagination: {
      type: Boolean,
      default: () => true
    },
    loadingTag: {
      type: String,
      default: () => ''
    },
    options: {
      type: Object,
      default() {
        return this.gOptions
      }
    },
    pageOptions: {
      type: Object,
      default() {
        return this.gPageOptions
      }
    },
    data: {
      type: Array,
      default: ()=>[]
    },
    columns: {
      type: Array,
      default: ()=>[]
    }
  }
}
</script>
<style scoped>

</style>