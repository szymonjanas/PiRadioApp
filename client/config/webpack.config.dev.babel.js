// Import webpack
import webpack from 'webpack';

// Import webpack plugins
import { merge as webpackMerge } from 'webpack-merge';

// Import common configuration
import baseConfig from './webpack.config.base.babel';

export default webpackMerge(baseConfig, {
  mode: 'development',

  devtool: 'source-map',

  devServer: {
    // Enable gzip compression of generated files.
    compress: true,

    historyApiFallback: true,

    watchOptions: {
      aggregateTimeout: 300,
      poll: 1000,
    },

    stats: {
      colors: true,
    },

    // Enable hot reloading server.
    hot: true,

    // embed the webpack-dev-server runtime into the bundle
    inline: true,

    disableHostCheck: true,

    overlay: true,
  },

  plugins: [
    new webpack.HotModuleReplacementPlugin(),
  ],
});
