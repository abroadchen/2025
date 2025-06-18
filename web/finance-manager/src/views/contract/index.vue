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
      <template v-slot:status="col">
        <el-table-column align="center" width="140" :prop="col.prop" :label="col.label">
          <template v-slot="{row}">
            <el-tag :type="row.status | contractColor">{{row.status | contractText }}</el-tag>
          </template>
        </el-table-column>
      </template>
      <template v-slot:opts="col">
        <el-table-column  :label="col.label" :width="col.width">
          <template v-slot="{row}">
            <el-button :disabled="row.status > 5" @click="genContract(row.id)" type="primary">生成合同</el-button>
            <el-button :disabled="row.status < 5" @click="downloadContractFile(row.id)" type="success">下载合同</el-button>
          </template>
        </el-table-column>
      </template>
    </GTable>

  </div>
</template>
<script>
import conf from './conf'
import { pager, crud } from "@/mixins"
import { convertBirthday } from "@/filters"
import Vue from "vue"
import {
  genContractFile,
  downloadContract
} from "@/apis/loan"
import { downloadFile } from '@/utils'

export default {
  name: 'contract',
  mixins: [pager, crud],
  methods: {
    async genContract(id) {
      if (!await this.confirm('是否确定生成合同?')) return
      let [res, err] = await approveFirstPass(id)
      if (!res) return
      this.init()
    },
    async downloadContractFile(id) {
      if (!await this.confirm('是否确定下载合同?')) return
      let [res, err] = await approveFirstReject(id)
      if (!res) return
      let url = res?.data?.data?.url
      if (!url) return this.$message.error(res.data.data)
      await downloadFile(url.replace('/api', ''), '贷款合同-' + id + '.docx')
    },
    showInfo(row) {
      this.dialogVisible = true
      let filterFn = Vue.filter('birthday')
      this.editConf = {
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
      }
    },
    beforeInit() {
      this.url = '/contract/list'
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
      loadingTag: 'tab7',
      tableData: [],
      dialogVisible: false,
      editConf: {}
    }
  }
}
</script>
<style scoped></style>