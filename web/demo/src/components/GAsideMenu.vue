<template>
  <el-sub-menu v-if="item.children" index="item.path">
      <template #title>
        <span>{{item.meta.title}} </span>
      </template>
      <GAsideMenu v-for="i in item.children" :item="i"/>
  </el-sub-menu>
  <el-menu-item v-else index="item.path">
    <span>{{item.meta.title}}</span>
  </el-menu-item>
</template>

<script lang="ts">
interface Menu {
  item: {
    meta: {
      title?: string;
    },
    path: string,
    children?: Menu[]
  }
}
export default {
  name: 'GAsideMenu',
}
</script>

<script  lang="ts" setup>
defineProps<Menu>()
</script>