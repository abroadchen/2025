export default Object.freeze({
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
            label: "出生日期",
            prop: "birthday",
            slot: 'birthday'
        },
        {
            label: "身份证",
            prop: "identity_card",
        },
        {
            label: "操作",
            width: 1000,
            prop: "opts",
            slot: "opts",
        },
    ]
})