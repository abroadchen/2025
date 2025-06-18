<template>
  <div id="login">
    <div id="login-box">
      <h2>登录系统</h2>
      <el-form ref="formRef" :rules="rules" :model="form" label-width="120px">
        <el-form-item label="用户名" prop="account">
          <el-input v-model="form.account"/>
        </el-form-item>
        <el-form-item label="密码" prop="password">
          <el-input v-model="form.password"/>
        </el-form-item>
      </el-form>
      <el-button type="primary" @click="doSubmit(formRef)">提交</el-button>
    </div>
  </div>
</template>
<script lang="ts" setup> //不用return
// import {useUser} from "@/store/user";
// const store = useUser();
// const test = function () {
//   store.login()
//   store.setUserInfo({
//     account: 'admin',
//   })
//   console.log(store.menus, store.isLogin)
// }
import { reactive, ref } from "vue"
import User, { IUser } from "@/models/User"
import { FormInstance } from "element-plus"
import { doLogin } from "@/api/user";
import {useUser} from "@/store/user";
import { useRoute } from 'vue-router'
import router from "@/router";
const user = useUser()
const route = useRoute()
const formRef = ref()
const rules = { //不用响应式 不改
  account: [{ required: true, message: "请输入用户名", trigger: "blur" }],
  password: [{ required: true, message: "请输入密码", trigger: "blur" }]
}
const form: IUser = reactive(new User())
const doSubmit = (form1: FormInstance) => {
  // formRef.value.validate

  form1.validate(async (valid:boolean)=>{
    if (valid) {
      console.log('验证成功')
      const res = await doLogin(form)
      user.login()
      const redirect = route.query.redirect as string
      await router.push(redirect || '/')
    } else {
      console.log('验证失败')
    }
  })
}
</script>

<style scoped lang="scss">
#login {
  width: 100%;
  height: 100%;
  background: url("../assets/img/bg.jpg");
  background-size: cover;
  position: relative;
}
#login-box {
  width: 650px;
  height: 220px;
  position: absolute;
  left: 50%;
  top: 50%;
  transform: translate(-50%, -50%);
  border: 1px solid gray;
  border-radius: 4px;
  background-color: #fff;
}
#login-box h2 {
  text-align: center;
  margin-top: 20px;
}
</style>