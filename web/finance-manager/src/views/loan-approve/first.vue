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
      <template #birthday="col">
        <el-table-column width="170" :prop="col.prop" :label="col.label">
          <template v-slot="{row}">
            <span>{{row.birthday | birthday}}</span>
          </template>
        </el-table-column>
      </template>
      <template v-slot:opts="col">
        <el-table-column  :label="col.label" :width="col.width">
          <template v-slot="{row}">
            <el-button @click="showInfo(row)" type="primary">查看</el-button>
            <el-button @click="pass(row.id)" type="success">通过</el-button>
            <el-button @click="reject(row.id)" type="danger">拒绝</el-button>
          </template>
        </el-table-column>
      </template>
    </GTable>
    <el-dialog
        title="贷款审批-查看详情"

        :visible.sync="dialogVisible"
        width="30%">
<!--      <GFormCreator v-if="exist" :conf="editConf" @submit="save"></GFormCreator>-->
            <GFormCreator :nonCheck="true" :conf="editConf" :key="Math.random()">
              <template>
                <el-button @click="dialogVisible = false">取消</el-button>
              </template>
            </GFormCreator>
    </el-dialog>
  </div>
</template>
<script>
import conf from './conf'
import { pager, crud } from "@/mixins"
import { convertBirthday } from "@/filters"
import Vue from "vue"
import {
  approveFirstPass,
  approveFirstReject
} from "@/apis/loan"

export default {
  name: 'loan-approve-first',
  mixins: [pager, crud],
  methods: {
    async pass(id) {
      if (!await this.confirm('是否确定初审通过?')) return
      let [res, err] = await approveFirstPass(id)
      if (!res) return
      this.init()
    },
    async reject(id) {
      if (!await this.confirm('是否确定初审拒绝?')) return
      let [res, err] = await approveFirstReject(id)
      if (!res) return
      this.init()
    },
    showInfo(row) {
      this.dialogVisible = true
      let filterFn = Vue.filter('birthday')
      this.editConf = Object.freeze({
        items: [
            [{ key: 'id', label:'id', value: row.id }],
            [{ key: 'name', label:'姓名', value: row.name }],
            [{ key: 'birthday', label:'出生日期', value: filterFn(row.birthday) }],
            [{ key: 'sex', label:'性别', value: row.sex}],
            [{ key: 'education', label:'教育程度', value: row.education}],
            [{ key: 'address1', label:'居住地址', value: row.address1}],
            [{ key: 'mobile_phone', label:'手机号', value: row.mobile_phone}],
            [{ key: 'identity_card', label: '身份证号', value: row.identity_card}]
        ].map(rowArr => rowArr.map(item => ({ ...item, type: 'input', colspan: 24, attrs:  { disabled: true }})))
      })
    },
    beforeInit() {
      this.url = '/approve/first/list'
      this.customField = {
        loadingTag: this.loadingTag
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
      loadingTag: 'tab2',
      tableData: [],
      dialogVisible: false,
      editConf: {}
    }
  }
}
</script>
<style scoped></style>