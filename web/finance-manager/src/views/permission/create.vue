<template>
  <GFormCreator ref="createForm" :conf="createConf" @submit="doSubmit">
    <template #default>
      <div class="left">
        <el-button @click="doCreate" type="primary">创建管理员</el-button>
        <el-button @click="doReset">重置</el-button>
      </div>
    </template>
  </GFormCreator>
</template>

<script>
import createConf from "./createFormConf";
import { createUser } from "@/apis/user";

export default {
  name: 'permission-create',
  methods: {
    doSubmit(data) {
      console.log('提交事件触发', data)
    },
    doCreate() {
      // let res = this.$refs.createForm.getData()
      // console.log('提交获取数据', res)
      this.$refs.createForm.validate(async data =>{
        if (data) {
          console.log('验证成功', data)
          let [res, err] = await createUser(data)
          if (err) return this.$message('创建失败')
          this.$message('创建成功')
        } else {
          console.log('验证失败')
        }
      })
    },
    doReset() {
      this.$refs.createForm.reset()
    }
  },
  data() {
    return {
      createConf
    }
  }
}
</script>

<style></style>