import loaderUtils from 'loader-utils'

export default function (content) {

  var callback = this.async()
  setTimeout(() => {
    let op = loaderUtils.getOptions(this)
    callback(null, content.replace(/xx/g, op.val))
  }, 3000)

}