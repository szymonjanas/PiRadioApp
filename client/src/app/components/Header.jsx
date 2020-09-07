import React from 'react';

import { SidebarButton } from './SidebarButton';

const Header = () => {
  return (
    <header className="header">
      <SidebarButton />
      <h1 className="heading">PiRadio</h1>
    </header>
  );
};

export { Header };
