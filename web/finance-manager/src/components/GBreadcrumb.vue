<template>
  <el-breadcrumb separator="/">
    <el-breadcrumb-item v-for="(route, i) in breadcrumbList" :key="i">
      <span v-if="breadcrumbList.length - 1 === i">{{route?.meta?.title}}</span>
      <router-link v-else :to="route">{{route?.meta?.title}}</router-link>
    </el-breadcrumb-item>
  </el-breadcrumb>
</template>
<script>
export default {
  computed: {
    breadcrumbList() {
      return this.$route.matched.filter(route => route?.meta?.title)
    }
  },
  // data() {
  //   return {
  //     breadcrumbList: []
  //   }
  // },
  // created() {
  //   this.breadcrumbList = this.$route.matched.filter(route => route?.meta?.title)
  // },
  // watch: {
  //   $route: {
  //     deep: true,
  //     handler() {
  //       this.breadcrumbList = this.$route.matched.filter(route => route?.meta?.title)
  //     },
  //     immediate: true
  //   }
  // },
  name: 'GBreadcrumb',
}
</script>
<style></style>