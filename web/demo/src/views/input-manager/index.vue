<template>
  <el-input v-model="name" @input="changeName" style="width: 240px" placeholder="Please input" />
  <el-table :data="data.tableData" style="width: 100%">
    <el-table-column type="index" width="50" />
    <el-table-column type="selection" :selectable="selectable" width="55" />
    <el-table-column
      v-for="col in columns" :label="col.label" :prop="col.prop"
    ></el-table-column>
    <el-table-column label="Name" width="180">
      <template #default="scope">
        <el-tag type="success">{{ scope.row.name }}</el-tag>
      </template>
    </el-table-column>
    <el-table-column label="Operations">
      <template #default="scope">
        <el-button size="small" @click="handleEdit(scope.row)">
          Edit
        </el-button>
        <el-button
            size="small"
            type="danger"
            @click="handleDelete(scope.row)"
        >
          Delete
        </el-button>
        <el-button size="small" type="success" @click="handleEdit(scope.row)">
          commit
        </el-button>
      </template>
    </el-table-column>
  </el-table>
  <el-pagination
      v-model:current-page="pager.pageNo"
      v-model:page-size="pager.pageSize"
      :page-sizes="[100, 200, 300, 400]"
      layout="total, sizes, prev, pager, next, jumper"
      :total="400"
      @size-change="handleSizeChange"
      @current-change="handleCurrentChange"
  />
</template>

<script lang="ts" setup>
import {reactive, ref, watchEffect } from "vue"
import { queryLoanList } from "@/api/loan";


const data = reactive({
  tableData: []
})
const pager = reactive({
  name: "",
  pageNo: 1,
  pageSize: 10
});
const total = ref(0)



const columns = [
    {
      label: "Name",
      prop: "name"
    },
    {
      label: "Age",
      prop: "age"
    },
    {
      label: "Address",
      prop: "address"
    }
]

const debounce = function (fn: any, delay: number) {
  let timer: any = null
  return function () {
    clearTimeout(timer)
    timer = setTimeout(() => {
      fn(...arguments)
    }, delay)
  }
}
const name = ref('')
const changeName = debounce((val: any) => {
  pager.name = val
}, 1000)


const handleEdit = (row: any) => {}
const handleDelete = (row: any) => {}

function handleSizeChange(size: any) {
  pager.pageSize = size
  pager.pageNo = 1
  init()
}

function handleCurrentChange(page: any) {
  pager.pageNo = page
  init()
}



const init = async () => {
  const res = await queryLoanList(pager)
  data.tableData = res.data.data?.data?.data
  total.value = res.data.data.rows
}

watchEffect(
  init
)

init()

</script>