let audio = document.querySelector('audio');
let aroundPlay = document.querySelector('.around_play');

aroundPlay.addEventListener('click', switchState);

function switchState() {

    if (audio.paused) { audio.play(); aroundPlay.textContent = 'stop'; } else {
        audio.pause(); aroundPlay.textContent = 'play';
    }

}