<template>
    <div class="login-box">
      <div class="login-input-box center">
        <h1>信贷管理系统</h1>

        <el-form :model="ruleForm" status-icon :rules="rules" ref="ruleForm" class="demo-ruleForm">
          <el-form-item  prop="username">
            <el-input prefix-icon="el-icon-user-solid" v-model="ruleForm.username"></el-input>
          </el-form-item>
          <el-form-item  prop="pass">
            <el-input prefix-icon="el-icon-s-order" type="password" v-model="ruleForm.pass" autocomplete="off"></el-input>
          </el-form-item>

          <el-form-item>
            <el-button type="primary" @click="submitForm">提交</el-button>
          </el-form-item>
        </el-form>


      </div>
    </div>
</template>
<script>
import { mapMutations } from "vuex";

import {doLogin} from "@/apis/user";

export default {
  mounted() {
    this.enterLogin = (e) => {
      if (e.key === 'Enter') {
        this.doLogin(this.ruleForm)
      }
    }
    window.addEventListener("keypress", this.enterLogin)
  },
  beforeDestroy() {
    window.removeEventListener("keypress", this.enterLogin)
  },
  data() {
    var validatePass = (rule, value, callback) => {
      if (value === '') {
        callback(new Error('请输入密码'));
      } else if (value.length < 6) {
        callback(new Error('密码不能小于6位数'));
      } else {
        callback();
      }
    };
    return {
      ruleForm: {
        username: '',
        pass: '',
      },
      rules: {
        pass: [
          {validator: validatePass, trigger: 'blur'}
        ],
        username: [
          {required:true, trigger: 'blur'}
        ],
      }
    };
  },
  methods: {
    ...mapMutations({
      changeLogin: 'user/changeIsLogin',
      changeUserInfo: 'user/changeUserInfo'
    }),
    async doLogin(form) {
      const [res, err] = await doLogin(form);
      if (err) {
        this.$message.error('请求异常' + err.message);
      }
      console.log(userInfo, "解密");
      if (res.data.code === 20000) {
        let userInfo;
        if (res?.data?.data?.token) {
          // userInfo = jwt.decode(res?.data?.data?.token, "");
          this.changeUserInfo({
            username: form.username
          });
        }
        this.changeLogin(true);

        this.$router.push(this.$route.query.redirect || '/');
      } else {
        this.$message.error('登录失败!!!');
      }
    },
    submitForm() {
      this.$refs.ruleForm.validate((valid) => {
        if (valid) {
          this.doLogin(this.ruleForm);
        } else {
          console.log('error submit!!');
          return false;
        }
      });
    },
  }
}
</script>
<style lang="scss" scoped>
.login-input-box {
  width: 650px;
  height: 320px;
  background: #fff;
  text-align: center;
  padding: 40px 40px 12px 12px;
}
.login-box {
  height: 100%;
  background: url("../assets/OIP-C.jpeg");
  background-size: cover;
}
.el-button {
  width: 600px;
}
.el-input {
  width: 600px;
  margin-bottom: 16px;
}
:deep(.el-input__inner) {
  background: #e5e5e5;
}
</style>
