<template>
  <el-breadcrumb :separator-icon="ArrowRight">
    <el-breadcrumb-item v-for="(route, i) in breadcrumbList">
      <span v-if="breadcrumbList.length - 1 === i">
        {{route?.meta?.title}}
      </span>
      <router-link v-else :to="route">{{route?.meta?.title}}</router-link>
    </el-breadcrumb-item>
  </el-breadcrumb>
</template>

<script lang="ts">
export default {
  name: 'GBreadcrumb'
}
</script>


<script lang="ts" setup>
import { ArrowRight } from '@element-plus/icons-vue'
import { useRoute } from 'vue-router'
import { computed } from "vue"

const route = useRoute()
const breadcrumbList = computed(() => {
  return route.matched.filter(item => item?.meta?.title)
})
</script>

<style lang="less" scoped>
</style>