import { Loading, Message, Notification, MessageBox } from 'element-ui'

function confirm(context) {
    return  MessageBox.confirm(context, '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
    }).then(()=>{
        return  true
    }).catch(()=>{
        Message.error({
            type: 'info',
            message: '已取消删除'
        })
        return false
    })
}

function install (Vue) {
    Object.defineProperties(Vue.prototype, 'confirm', {
        set  () {
        },
        get () {
            return confirm
        }
    })
}


export default {
  install
}