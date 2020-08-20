// Import webpack
import webpack from 'webpack';

// Import webpack plugins
import { merge as webpackMerge } from 'webpack-merge';
import TerserPlugin from 'terser-webpack-plugin';

// Import common configuration
import baseConfig from './webpack.config.base.babel';

export default webpackMerge(baseConfig, {
  mode: 'production',

  stats: {
    maxModules: 0,
  },

  // Don't attempt to continue if there are any errors
  bail: true,

  devtool: 'cheap-module-source-map',

  plugins: [
    new webpack.optimize.OccurrenceOrderPlugin(),
  ],

  optimization: {
    minimize: true,
    minimizer: [
      new TerserPlugin({
        cache: true,
        parallel: true,
        sourceMap: true,
        extractComments: false,
        terserOptions: {
          output: {
            comments: false,
          },
        },
      }),
    ],
    splitChunks: {
      cacheGroups: {
        default: false,
        commons: {
          test: /[\\/]node_modules[\\/]/,
          name: 'vendor',
          chunks: 'all',
        },
      },
    },
  },
});
