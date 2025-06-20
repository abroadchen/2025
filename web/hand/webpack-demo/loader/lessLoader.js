import less from 'less'
export default function (content) {
  // let callback = this.async()
  let css = ''
  less.render(content, (err, result) => {
    // callback(err, result.css)
    css = result.css
  })
  return css
}