import React from 'react';

const Player = () => {
  return (
    <div className="player-wrapper">
      <div className="player-controls">
        <div className="player-controls__item">
          <button type="button">
            <span className="icon--previous"></span>
          </button>
        </div>
        <div className="player-controls__item player-controls__item--play">
          <button type="button">
            <span className="icon--play"></span>
          </button>
        </div>
        <div className="player-controls__item">
          <button type="button">
            <span className="icon--next"></span>
          </button>
        </div>
      </div>
      <div className="player__status">
        <span className="player__message">Currently playing: PiRadio Station</span>
      </div>
    </div>
  );
};

export { Player };
