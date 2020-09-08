import { INITIAL_STATE, ACTIONS } from './constants';

export const sidebarReducer = (state = INITIAL_STATE, action) => {
  switch (action.type) {
    case ACTIONS.OPEN_SIDEBAR:
      return {...state, sidebarVisible: true };
    case ACTIONS.CLOSE_SIDEBAR:
      return {...state, sidebarVisible: false }
    default:
      return INITIAL_STATE;
  }
}
