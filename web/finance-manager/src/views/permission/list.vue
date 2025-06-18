<template>
  <div id="approve">
    <GSearchQuery @setValue="setQueryName"></GSearchQuery>
    <GTable :options="conf.options"
            :pageOptions="frontPageOptions"
            :loading-tag="loadingTag"
            :data="tableData"
            :columns="conf.columns"
            @handleCurrentChange="currentPageChange"
            @size-change="sizeChange"
    >
      <template #reg_time="col">
        <el-table-column width="170" :prop="col.prop" :label="col.label">
          <template v-slot="{row}">
            <span>{{row.reg_time | birthday}}</span>
          </template>
        </el-table-column>
      </template>
      <template #role_name="col">
        <el-table-column width="170" :prop="col.prop" :label="col.label">
          <template v-slot="{row}">
            <span>{{row.role_name | role }}</span>
          </template>
        </el-table-column>
      </template>
    </GTable>

  </div>
</template>
<script>
import conf from './conf'
import { pager, crud } from "@/mixins"


export default {
  name: 'permission-list',
  mixins: [pager, crud],
  methods: {


    beforeInit() {
      this.url = '/user/list'
      this.customField = {
        loadingTag: this.loadingTag
      }
      this.params = {
        type: 'new'
      }
      return true
    },
    afterInit(data) {

    }
  },
  created() {
    this.init()
  },
  data() {
    return {
      conf: conf,
      loadingTag: 'tab8',
      tableData: [],
      dialogVisible: false,
      editConf: {}
    }
  }
}
</script>
<style scoped></style>