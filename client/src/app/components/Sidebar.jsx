import React from 'react';

import { STREAMING_URLS } from '../constants';

import { AppContext } from '../App';

const Sidebar = () => {
  // eslint-disable-next-line no-unused-vars
  const {state, dispatch} = React.useContext(AppContext);

  const handleClick = () => {
    dispatch({ type: 'CLOSE_SIDEBAR' });
  }

  return (
    <div className="sidebar">
      <div className="sidebar__header">
        <h2 className="sidebar__heading">Stations</h2>
        <button className="sidebar__back-button" onClick={handleClick}>
          <span className="icon--angle-left"></span>
        </button>
      </div>
      <ul className="station-list">
        {STREAMING_URLS.map(item => (
          <li
            key={item.id}
            className="station-list__item"
          >
            <div className="station-list__item-body">
              <button type="button" className="station-list__button">
                <span className="icon--play"></span>
              </button>
              <h3>{item.name}</h3>
            </div>
          </li>
        ))}
      </ul>
    </div>
  );
};

export { Sidebar };
