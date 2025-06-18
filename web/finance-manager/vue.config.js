const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true
})

module.exports = {
  chainWebpack: config => {},
    devServer: {
      proxy: {
        '/api': {
          target: 'http://1.116.64.64:5004/',
          changeOrigin: true,
        }
      }
    }
}