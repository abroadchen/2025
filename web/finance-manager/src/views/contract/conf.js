export default {
    options: {
        useIndex: false,
        useMultiSelect: false
    },
    columns: [
        {
            label: "姓名",
            prop: "name",
        },

        {
            label: "身份证",
            prop: "identity_card",
        },
        {
            label: "合同状态",
            prop: "status",
            slot: 'status'
        },
        {
            label: "操作",
            width: 1000,
            prop: "opts",
            slot: "opts",
        },
    ]
}