export default Object.freeze({
    options: {
        loading: true,
        useIndex: false,
        useMultiSelect: true
    },
    pageOptions: {},
    columns: [

        {
            label: "姓名",
            prop: "name",
            width: "20"
        },
        {
            label: "出生日期",
            prop: "birthday",
            slot: 'birthday'
        },
        {
            label: "性别",
            prop: "sex",
            slot: 'sex'
        },
        {
            label: "教育程度",
            prop: "education",
            slot: 'education'
        },
        {
            label: "居住地址",
            prop: "address1",
        },
        {
            label: "手机号",
            prop: "mobile_phone",
            isHide: false
        },
        {
            label: "申请状态",
            prop: "status",
            slot: "status"
        },
        {
            label: "操作",
            prop: "opts",
            slot: "opts",
            width: 500
        },
        {
            label: '配送信息',
            children: [
                {
                    label: '地址',
                    children: [
                        {label: '省份'},
                        {label: '市区'},
                        {label: '详细地址'}
                    ]
                }
            ]
        },
        {
            label: '自定义html',
            formatter: function (prop) {
                return <div>
                    <h2>${prop.row.name}</h2>
                    <button>${prop.$index}</button>
                </div>
            }
        }
    ]
})