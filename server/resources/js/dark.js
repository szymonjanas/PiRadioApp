
let play = document.querySelector('.play');
let arounPlay = document.querySelector('.around_play');
let audio = document.querySelector('audio');

arounPlay.addEventListener('click', function () {

    if (play.className === 'play') { play.className = 'play playing'; audio.play(); } else { play.className = 'play'; audio.pause(); }

});