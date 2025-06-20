import fs from 'fs'
import {path as p} from 'path'

class MyCleanWebpackPlugin { 
  constructor() {}

  apply(compiler) {
  
    let outputPath = compiler.config.output.path
    compiler.hooks.entryOption.tap('MyCleanWebpackPlugin', () => {
      this.cleanDir(outputPath)
    })
  
  }

  cleanDir(path) {
    if (!fs.existsSync(path)) return
    if (fs.statSync(path).isDirectory() && fs.readdirSync(path).length > 0) {
      let files = fs.readdirSync(path)
      files.forEach((file) => {
        let filePath = p.resolve(path, file)
        if (fs.statSync(filePath).isDirectory()) {
          this.cleanDir(filePath)
        } else {
          fs.unlinkSync(filePath)
        }
      })
      fs.rmdirSync(path)
    }
  }
}

export default MyCleanWebpackPlugin