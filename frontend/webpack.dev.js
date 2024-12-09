/** @format */
const { merge } = require("webpack-merge")
const common = require("./webpack.common.js")

const host = process.env.KORP_HOST || "localhost"
const port = process.env.KORP_PORT || 9000

let server
if (process.env.KORP_HTTPS) {
    server = {
        type: "https",
        options: {
            key: process.env.KORP_KEY,
            cert: process.env.KORP_CERT,
        },
    }
} else {
    https = false
    server = "http"
}

allowedHosts = ["andmebaas.zapto.org"]

module.exports = merge(common, {
    devServer: {
        host,
        port,
        server,
        allowedHosts,
    },
    devtool: "inline-source-map",
    optimization: {
        // Needed for hot reloading with multiple entrypoints
        runtimeChunk: "single",
    },
    mode: "development",
})
