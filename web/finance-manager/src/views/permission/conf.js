export default {
    options: {
        useIndex: false,
        useMultiSelect: false
    },
    columns: [
        {
            label: "用户名",
            prop: "account"
        },
        {
            label: "密码",
            prop: "password"
        },
        {
            label: "创建时间",
            prop: "reg_time",
            slot: 'reg_time'
        },
        {
            label: "创建者",
            prop: "creator"
        },
        {
            label: "权限分配",
            prop: "role_name",
            slot: 'role_name'
        }
    ]
}