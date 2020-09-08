import React from 'react';

import { CSSTransition } from 'react-transition-group';

import { Sidebar } from './components/Sidebar';
import { Header } from './components/Header';
import { Player } from './components/Player';

import { sidebarReducer } from './reducers';

import { INITIAL_STATE, SLIDE_ANIMATION_DURATION } from './constants';

export const AppContext = React.createContext();

const App = () => {
  const [state, dispatch] = React.useReducer(sidebarReducer, INITIAL_STATE);

  return (
    <AppContext.Provider value={{ state, dispatch }}>
      <div className="site-wrapper">
        <CSSTransition
          in={state.sidebarVisible}
          timeout={SLIDE_ANIMATION_DURATION}
          classNames="sidebar"
          unmountOnExit
        >
          <Sidebar />
        </CSSTransition>
        <Header/>
        <main role="main" className="site-content">
          <Player />
        </main>
      </div>
    </AppContext.Provider>
  );
};

export { App };
