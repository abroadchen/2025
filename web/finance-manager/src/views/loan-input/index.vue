<template>
  <GFormCreator ref="createForm" :conf="inputConf">
    <template>
      <div>
        <el-button @click="createUser" type="primary">立即创建</el-button>
        <el-button @click="reset">重置</el-button>
      </div>
    </template>
  </GFormCreator>
</template>

<script>
import inputConf from './inputPageConf'
import {createLoan} from "@/apis/loan";

export default {
  name: 'loan-input',
  methods: {
    createUser() {
      this.$refs.createForm.validate(async (data) => {
        if (!data) return this.$message('请填写完整信息')
        console.log('提交获取数据', data)
        // var mockdata = {}
        let [res, err] = await createLoan(data)
        if (err) return this.$message('创建失败')
        console.log(res, '创建成功')
      })
    },
    reset() {this.$refs.createForm.reset()}
  },
  data() {
    return  {
      inputConf
    }
  }
}
</script>

<style>

</style>