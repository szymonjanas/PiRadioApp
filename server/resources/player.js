var state = 'stop'

var play_img = "img/play.png"
var stop_img = "img/stop.png"
console.log(state)
function button_state(){
    console.log("State: ")
    var btn_img = document.getElementById("button_state_img");
    if (state == 'stop'){
        console.log("playing...")
        state = 'play';
        btn_img.src = stop_img;
    } else {
        console.log("stopping...")
        state = 'stop'
        btn_img.src = play_img;
    }
}


















