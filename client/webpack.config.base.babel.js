// Import webpack
import webpack from 'webpack';

// Import Node packages
import path from 'path';

// Import webpack plugins
import WebpackNotifierPlugin from 'webpack-notifier';
import HtmlWebpackPlugin from 'html-webpack-plugin';
import ExtractCssChunks from 'extract-css-chunks-webpack-plugin';
import StyleLintPlugin from 'stylelint-webpack-plugin';

// Import package.json
import PKG from './package.json';

const DEVELOPMENT = process.env.NODE_ENV === 'development' ? true : false;

export default {
  // The base directory for resolving `entry` (must be absolute path)
  context: path.resolve(__dirname, 'src'),

  entry: './index.js',

  output: {
    // The bundling output directory (must be absolute path)
    path: path.resolve(__dirname, 'dist'),

    // The output filename of the entry chunk, relative to `path`
    // [name] - Will be set per each key name in `entry`
    filename: '[name].js',
  },

  resolve: {
    extensions: ['*', '.js', '.jsx'],
    modules: [path.resolve(__dirname, 'src'), 'node_modules'],
  },

  module: {
    rules: [
      // Enforcing linting before build
      // The build should fail before it does anything else
      {
        enforce: 'pre',
        test: /\.jsx?$/,
        exclude: /node_modules/,
        loader: 'eslint-loader',
        options: {
          formatter: require('eslint-formatter-friendly'),
          cache: DEVELOPMENT,
          configFile: path.resolve(__dirname, '.eslintrc.json'),
        },
      },

      // Process JS(X) with Babel
      {
        test: /\.jsx?$/,
        exclude: /node_modules/,
        use: {
          loader: 'babel-loader',
        },
      },

      // Process Sass/SCSS and CSS files
      {
        test: /\.(sa|sc|c)ss$/,
        use: [
          {
            loader: ExtractCssChunks.loader,
            options: {
              hmr: DEVELOPMENT,
            },
          },
          'css-loader?sourceMap',
          'postcss-loader?sourceMap',
          'sass-loader?sourceMap',
        ],
      },

      // Process images
      {
        test: /\.(png|svg|jpg|gif)$/,
        use: [
          {
            loader: 'file-loader',
          },
        ],
      },

      // Process fonts
      {
        test: /\.(woff|woff2|eot|ttf|otf)$/,
        use: [
          {
            loader: 'file-loader?',
          },
        ],
      },
    ],
  },

  plugins: [
    new webpack.optimize.ModuleConcatenationPlugin(),
    new webpack.NoEmitOnErrorsPlugin(),
    new WebpackNotifierPlugin({
      title: PKG.description,
      message: 'Compilation done!',
      alwaysNotify: true,
    }),
    new HtmlWebpackPlugin({
      template: require('html-webpack-template'),
      inject: false,
      hash: true,
      appMountId: 'app',
      title: PKG.description,
      meta: [
        {
          name: 'description',
          content: PKG.description,
        },
      ],
      mobile: true,
      minify: {
        removeComments: true,
        collapseWhitespace: true,
        collapseInlineTagWhitespace: true,
        removeRedundantAttributes: true,
        useShortDoctype: true,
        removeEmptyAttributes: true,
        removeStyleLinkTypeAttributes: true,
        keepClosingSlash: true,
        minifyJS: true,
        minifyCSS: true,
        minifyURLs: true,
      },
    }),
    new ExtractCssChunks({
      filename: '[name].css',
      chunkFilename: '[id].css',
    }),
    new StyleLintPlugin(),
  ],
};
