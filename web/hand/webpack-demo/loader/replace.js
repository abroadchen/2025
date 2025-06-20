import loaderUtils from 'loader-utils'

export default function (content) {


  let op = loaderUtils.getOptions(this)
  return content.replace(/xx/g, op.val)
}