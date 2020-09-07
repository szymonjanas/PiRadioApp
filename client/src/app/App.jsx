import React from 'react';

import { Header } from './components/Header';
import { Player } from './components/Player';

const App = () => {
  return (
    <div className="site-wrapper">
      <Header />
      <main role="main" className="site-content">
        <Player />
      </main>
    </div>
  );
};

export { App };
