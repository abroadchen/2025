export default {
    name: 'drag',
    handler: {
        unbind: function (el){
            let target = el.getElementsByClassName('el-table__body-wrapper')[0]
            target.onmousedown = null
        },
        inserted: function (el, binding, vnode) {
            let target = el.getElementsByClassName('el-table__body-wrapper')[0]
            target.style.overflowX = 'hidden'
            target.style.cursor = 'grab'

            target.onmousedown = function (event) {
                let startPointX = event.clientX
                let startScrollLeft = target.scrollLeft
                document.onmousemove = function (e) {
                    let x = e.clientX - startPointX
                    target.scrollLeft = startScrollLeft - x
                }
                document.onmouseup = function () {
                    document.onmouseup = null
                    document.onmousemove = null
                }
            }
        }
    }
}