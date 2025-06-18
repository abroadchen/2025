<template>
  <div class="common-layout">
    <el-container>
      <el-aside width="200px">
        <el-menu
            default-active="2"
            class="el-menu-vertical-demo"
            router
        >
          <GAsideMenu v-for="menu in menus" :item="menu"></GAsideMenu>
        </el-menu>
      </el-aside>
      <el-container>
        <el-header>
          <GBreadcrumb/>
        </el-header>
        <el-main>
          <router-view></router-view>
        </el-main>
        <el-footer>Footer</el-footer>
      </el-container>
    </el-container>
  </div>
</template>
<script lang="ts" setup>
import { useUser } from "@/store/user"
import { storeToRefs } from "pinia"
import GBreadcrumb from "@/components/GBreadcrumb.vue";
const user = useUser()
const { menus } = storeToRefs(user)
</script>
<style scoped lang="scss">
.el-header, .el-footer {
  background-color: #B3C0D1;
  color: #333;
  text-align: center;
  line-height: 60px;
}

.el-aside {
  background-color: #D3DCE6;
  color: #333;
  text-align: center;
  line-height: 200px;
}

.el-main {
  background-color: #E9EEF3;
  color: #333;
  text-align: center;
  line-height: 160px;
}

body > .el-container {
  margin-bottom: 40px;
}

</style>