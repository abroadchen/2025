<template>
<!--  <nav>-->
<!--    <router-link to="/">Home</router-link> |-->
<!--    <router-link to="/about">About</router-link>-->
<!--    <el-button type="primary" @click="test">确定</el-button>-->
<!--  </nav>-->
  <router-view/>
</template>
<script lang="ts">
import { defineComponent } from 'vue'
import Axios from 'axios'
import { doLogin as loginApi } from "@/api/user";

export default defineComponent({
  setup() {
    const test = async () => {
      const res = await loginApi({account: 'admin', password: '123456'})
      res.data.token
    }

    return  {
      test
    }
  }
})
</script>

<style lang="scss">

</style>
