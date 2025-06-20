import { resolve } from 'path'
import { CleanWebpackPlugin } from 'clean-webpack-plugin'


export const devtool = 'inline-source-map'
export const mode = 'development'
export const entry = './src/app.js'
export const output = {
  path: resolve(__dirname, 'dist'),
  filename: 'bundle.js'
}
export const resolveLoader = {
  modules: ['node_modules', './loader']
}
export const module = {
  rules: [
    {
      test: /\.js$/,
      loader: 'replace',
      options: { val: '' }
    },
    {
      test: /\.less$/,
      loader: ['styleLoader', 'lessLoader']
    }
  ]
}
export const plugins = [
  new CleanWebpackPlugin()
]