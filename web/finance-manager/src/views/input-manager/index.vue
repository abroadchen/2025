<template>
  <div id="input-manager">
    <GSearchQuery>
      <template v-slot="{q}">
        <el-button type="primary" @click="setQueryName(q)">搜索</el-button>
      </template>
    </GSearchQuery>
    <GTable :options="conf.options"
            :pageOptions="frontPageOptions"
            :loading-tag="loadingTag"
            :data="tableData"
            :columns="conf.columns"
            @handleCurrentChange="currentPageChange"
            @selection-change="onSelectionChange"
            @size-change="sizeChange"
    >
      <template #birthday="col">
        <el-table-column width="170" :prop="col.prop" :label="col.label">
          <template v-slot="{row}">
            <span>{{row.birthday | birthday}}</span>
          </template>
        </el-table-column>
      </template>
      <template #sex="col">
        <el-table-column align="center" width="170" :prop="col.prop" :label="col.label">
          <template v-slot="{row}">
            <span>{{row.sex| sex}}</span>
          </template>
        </el-table-column>
      </template>
      <template #education="col">
        <el-table-column align="center" width="170" :prop="col.prop" :label="col.label">
          <template v-slot="{row}">
            <span>{{row.education | education}}</span>
          </template>
        </el-table-column>
      </template>

      <template v-slot:status="col">
        <el-table-column align="center" width="100" :prop="col.prop" :label="col.label">
          <template v-slot="{row}">
            <el-tag :type="row.status | statusColor">{{row.status | status}}</el-tag>
          </template>
        </el-table-column>
      </template>
      <template v-slot:opts="col">
        <el-table-column  :label="col.label" :width="col.width">
          <template v-slot="{row}">
            <el-button @click="showEdit(row)" type="primary">编辑</el-button>
            <el-button @click="delLoan(row.id)" type="danger">删除</el-button>
            <el-button @click="submit(row.id)" type="success">提交审核</el-button>
          </template>
        </el-table-column>
      </template>
    </GTable>
    <el-dialog
        title="申请管理-编辑"
        @open="exist=true"
        @close="exist=false"
        :visible.sync="dialogVisible"
        width="30%">
      <GFormCreator v-if="exist" :conf="editConf" @submit="save"></GFormCreator>
<!--      <GFormCreator :conf="editConf" @submit="save" :key="Math.random()"></GFormCreator>-->
    </el-dialog>
  </div>
</template>
<script>
import loanListConf from "./loanListConf"
import {queryLoan} from "@/apis/loan"
import {pager,crud} from '@/mixins'
import {sexOptions} from "@/conf"
import {saveLoan, deleteLoan, submitApprove} from "@/apis/loan"

export default {
  name: 'input-manager',
  mixins: [pager,crud],
  created() {
    this.init()
  },

  methods: {
    async submit(id) {
      if (!await this.confirm('是否确定提交?')) return
      let [res, err] = await submitApprove(id)
      if (!res) return
      this.init()
    },
    async delLoan(id) {
      let isConfirm = await this.confirm('是否确定删除?')
      if (!isConfirm) return
      let [res, err] = await deleteLoan(id)
      this.init()
    },
    async save(data) {
       let [res, err] = await saveLoan({
        ...data,
        id: this.editingId
      })
      if (err) return this.message.error('请求失败')
      this.dialogVisible = false
      this.$notify.success({
        title: '提示',
        message: '编辑成功',
        showClose: false
      })
      this.init()
    },
    showEdit(row) {
      this.editingId = row.id
      this.editConf = {
        items: [
            [{ label:'姓名', value: row.name, key: 'name', type: 'input', colspan: 20}],
            [{ label: '性别', value: row.sex, options: sexOptions, key: 'sex', type: 'select', colspan: 20}]
        ],
        rules: {
          name: [{require: true, message: '必须填写用户名'}],
          sex: [{require: true, message: '必须填写性别'}]
        }
      }
      this.dialogVisible = true
    },
    beforeInit() {
      this.url = '/loan/list'
      this.customField = {
        loadingTag: this.loadingTag
      }
      return true
    },
    onSelectionChange() {

    },
  },
  data() {
    return {
      conf: loanListConf,
      tableData: [],
      loadingTag: 'tab1',
      dialogVisible: false,
      editConf: {},
      exist: false
    }
  }
}
</script>
<style></style>