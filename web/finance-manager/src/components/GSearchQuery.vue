<template>
  <el-row>
    <el-col :span="$scopedSlots.default?22:24">
      <el-input placeholder="请输入名称" type="text" v-model="query"></el-input>
    </el-col>
    <el-col :span="2">
      <slot :q="query"></slot>
    </el-col>
  </el-row>
</template>
<script>
import {debounce} from '@/utils'

export default {
  name: 'GSearchQuery',
  watch: {
    query() {
      if (this.$scopedSlots.default) return
      this.debounceQuery()
    }
  },
  data() {
    return {
      query: '',
      debounceQuery: debounce(()=>{
        this.$emit('setValue', this.query)
      }, 1000)
    }
  },
}
</script>
<style scoped>
.el-row {
  margin-bottom: 10px;
}
</style>