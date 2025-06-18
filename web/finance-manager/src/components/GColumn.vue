<template></template>
<script>
export default {
  name: 'GColumn',
  methods: {
    renderTableColumns(columns) {
      return columns.map((col,i) => {
        return this.renderTableCol(col,i)
      })
    },
    renderTableCol(col) {
      let scopedSlots
      if (col.formatter) {
        scopedSlots = {
          default: function (prop) {
            return <div domPropsInnerHTML={col.formatter(prop)}></div>
          }
        }
      }
      return  col.slot ? this.$scopedSlots[col.slot]?.(col) : !col.isHide && (
          <el-table-column
              label={col.label}
              prop={col.prop}
              width={col.width}
              scopedSlots={scopedSlots}>
            {col.children && col.children.length > 0 && this.renderTableColumns(col.children)}
          </el-table-column>)
    }
  },
  props: {
    column: {
      type: Object,
      require: true
    }
  },
  render() {
    return this.renderTableCol(this.columns)
  },
}
</script>
<style></style>