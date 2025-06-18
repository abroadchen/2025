<template>
  <el-dropdown @command="$emit('command', $event)">
    <span class="el-dropdown-link">
      {{title}}<i class="el-icon-arrow-down el-icon--right"></i>
    </span>
    <el-dropdown-menu #dropdown>
      <el-dropdown-item :key="i" v-for="(item, i) in items" :command="item.key">{{item.label}}</el-dropdown-item>
    </el-dropdown-menu>
  </el-dropdown>
</template>
<script>
export default {
  props: {
    title: {
      required: true,
      type: String
    },
    items: {
      type: Array,
      required: true
    }
  },
  name: 'GDropdown',
}
</script>
<style></style>