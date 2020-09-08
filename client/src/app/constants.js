export const SLIDE_ANIMATION_DURATION = window.innerWidth < 768 ? 250 : 500;

export const ACTIONS = {
  OPEN_SIDEBAR: 'OPEN_SIDEBAR',
  CLOSE_SIDEBAR: 'CLOSE_SIDEBAR',
};

export const INITIAL_STATE = {
  sidebarVisible: false,
};

export const STREAMING_URLS = [
  {
    id: 1,
    name: 'Anty-Radio',
    url: 'http://redir.atmcdn.pl/sc/o2/Eurozet/live/antyradio.livx?audio=5',
  },
  {
    id: 2,
    name: 'ESKA-ROCK',
    url: 'http://waw02-03.ic.smcdn.pl:8000/t041-1.mp3',
  },
  {
    id: 3,
    name: 'ESKA-WROCLAW',
    url: 'http://waw02-03.ic.smcdn.pl:8000/t044-1.mp3',
  },
  {
    id: 4,
    name: 'Melo-Radio',
    url: 'http://mel0101.cdn.eurozet.pl:8800/mel-net.mp3',
  },
  {
    id: 5,
    name: 'Open-FM',
    url: 'https://stream.open.fm/127?type=.mp3',
  },
  {
    id: 6,
    name: 'Open-FM-100hits',
    url: 'https://stream.open.fm/64?type=.mp3',
  },
  {
    id: 7,
    name: 'Open-FM-4FUN-TV',
    url: 'https://stream.open.fm/173?type=.aac',
  },
  {
    id: 8,
    name: 'Open-FM-Summer-Classic',
    url: 'https://stream.open.fm/173?type=.aac',
  },
  {
    id: 9,
    name: 'RMF-FM',
    url: 'http://195.150.20.7:80/rmf_fm',
  },
];
