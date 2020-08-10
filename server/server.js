let listStation = document.querySelector('#wrap_radio_set');
let listStationButton = document.querySelector('#arrow');
listStationButton.addEventListener('click', function () {
    if (listStation.style.display === 'none') { listStation.style.display = 'block'; } else { listStation.style.display = 'none'; }
    console.log('kk');
}
);
let audio = document.querySelector('audio');
let playPause = document.querySelector('#play_pause');

playPause.addEventListener('click', switchState);

function switchState() {

    if (audio.paused) { audio.play(); playPause.textContent = 'stop'; } else {
        audio.pause(); playPause.textContent = 'play';
    }

}
