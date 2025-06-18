
const isProduction = process.env.NODE_ENV === 'production'
const UglifyJsPlugin = require('uglifyjs-webpack-plugin')
const plugins  = []
const cdn = {
    dev: {
        css: [],
        js: []
    },
    build: {
        css: [],
        js: [
            'https://cdn.bootcss.net/ajax/libs/axios/0.27.2/axios.min.js',
            'https://cdn.bootcss.com/vue-router/3.5.4/vue-router.min.js',
            'https://cdn.bootcss.com/vue/2.6.11/vue.min.js',
        ]
    }
}
let externals = {}
const CompressionWebpackPlugin = require('compression-webpack-plugin')

if (isProduction) {
    plugins.push(new UglifyJsPlugin({
        uglifyOptions: {
            output: {
                comments: false
            },
            warnings: false,
            compress: {
                drop_console: true,
                drop_debugger: false,
                pure_funcs: ['console.log']
            }
        }
    }))
    plugins.push(new CompressionWebpackPlugin({
        test: /\.(js|json|css)$/i,
        threshold: 10240
    }))
    externals = {
        axios: 'axios',
        'vue-router': 'VueRouter',
        vue: 'Vue'
    }
}

module.exports = {
    productionSourceMap: !isProduction,
    configureWebpack: {
        devServer: {
            proxy: {
                '/api': {
                    target: 'http://1.116.64.64:5004/',
                    changeOrigin: true
                }
            }
        },
        plugins,
        externals
    },
    chainWebpack: conf => {
        config.plugin('html').tap(args=>{
            if (isProduction) {
                args[0].cdn = cdn.build
            } else {
                args[0].cdn = cdn.dev
            }
            return  args
        })
    }
}