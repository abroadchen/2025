import {sexOptions, companyOptions, marriageOptions, educationOptions} from "@/conf";

export default Object.freeze({
    cards: [
        {
            name: "个人基本信息",
            children: [
                [
                    { label: "姓名", key: "name", type: "input"},
                    { label: "出生日期", key: "birthday", type: "datetime"},
                    {
                        label: "性别",
                        key: "sex",
                        type: "select",
                        options: sexOptions
                    }
                ],
                [{ label: "身份证", key: "identity_card", type: "input"}],
            ]
        }
    ]
})