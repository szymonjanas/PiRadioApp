import React from 'react';
import ReactDOM from 'react-dom';

import { ErrorBoundary } from './ErrorBoundary';
import { App } from './app';

import './styles/main.scss';

const render = () => {
  ReactDOM.render(
    <ErrorBoundary>
      <App/>
    </ErrorBoundary>,
    document.getElementById('app')
  );
};

// Enable Webpack hot module replacement
if (module.hot) {
  module.hot.accept('./app', () => {
    render();
  });
}

render();
