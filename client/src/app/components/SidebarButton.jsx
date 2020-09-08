import React from 'react';

import { AppContext } from '../App';

const SidebarButton = () => {
  // eslint-disable-next-line no-unused-vars
  const {state, dispatch} = React.useContext(AppContext);

  const handleClick = () => {
    dispatch({ type: 'OPEN_SIDEBAR' });
  }

  return (
    <button type="button" className="sidebar-button" onClick={handleClick}>
      <span className="icon--menu"></span>
    </button>
  );
};

export { SidebarButton };
