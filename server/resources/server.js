
var Stations_List_Json = [];

let STATION_LIST_MAX_WIDTH_pt = 400;
var resolution = window.screen.availWidth;
var play_img = "radio/res/img/play.png"
var stop_img = "radio/res/img/stop.png"

let DEBUG = true;

/* COLORS */
var colors = class Colors {
    constructor(){
        this.col_background;
        
        this.col_title_background;
        this.col_title_name;
        this.col_title_border;
        
        this.col_station_card_background;
        this.col_station_radio_img_playing;
        this.col_station_radio_img;
        this.col_station_name;
        this.col_station_play;
        this.col_station_playing;
        
        this.col_player_play;
        this.col_player_stop;
        this.col_player_img;
        this.col_player_name;
        this.col_player_title;
        this.col_player_background;
        this.col_player_border;
    }
};

function load_colors() {

    colors.col_background = "#333344";
        
    colors.col_title_background = "#113344";
    colors.col_title_name = "#bbeecc";
    colors.col_title_border = "#445577";
    
    colors.col_station_card_background = "#334455";
    colors.col_station_radio_img_playing = "invert(45%) sepia(66%) saturate(845%) hue-rotate(310deg) brightness(90%) contrast(93%)";
    colors.station_radio_img = "invert(56%) sepia(6%) saturate(625%) hue-rotate(131deg) brightness(92%) contrast(87%)";
    colors.col_station_name = "#bbddcc";
    colors.col_station_play = "invert(78%) sepia(48%) saturate(625%) hue-rotate(353deg) brightness(88%) contrast(95%)";
    colors.col_station_playing = "invert(45%) sepia(66%) saturate(845%) hue-rotate(310deg) brightness(90%) contrast(93%)";
    
    colors.col_player_play = "invert(45%) sepia(66%) saturate(845%) hue-rotate(310deg) brightness(90%) contrast(93%)";
    colors.col_player_stop = "invert(64%) sepia(9%) saturate(2912%) hue-rotate(14deg) brightness(93%) contrast(85%)";
    colors.col_player_img = "invert(84%) sepia(30%) saturate(336%) hue-rotate(116deg) brightness(97%) contrast(86%)";
    colors.col_player_name = "#bbeecc";
    colors.col_player_title = "#bbeecc";
    colors.col_player_background = "#334455";
    colors.col_player_border = "#778888";

    document.body.style.setProperty("background", colors.col_background, "important");

    var header = document.getElementsByTagName("Header");
    for (var i = 0; i < header.length; i++) {
        header[i].style.background = colors.col_title_background;
        header[i].style.borderColor = colors.col_title_border;
    }

    document.getElementById("title_name").style.color = colors.col_title_name;

    var player = document.getElementsByTagName("Footer");
    for (var i = 0; i < player.length; i++) {
        player[i].style.background = colors.col_player_background;
        player[i].style.borderColor = colors.col_player_border;
    }


}

/* COLORS END */

window.onload = function() {
    // if (resolution > 600) {
    //     console.log("RESOL", resolution);
    //     var list = document.getElementById("STATIONS_LIST");
    //     var resPt = resolution*3/4;
    //     var move = ((resPt - STATION_LIST_MAX_WIDTH_pt)/2)-5;
    //     console.log ("TEST", move);
    //     var transform = "translateX("+move+"pt)";
    //     console.log(transform);
    //     list.style.transform = transform;

    // }

    document.getElementById("LIST").style.width = resolution + "px";
    reload();

};

function reload() {
    load_colors();
    load();
    load_player_state();
}

setInterval(function() {
    load();
}, 50000);

function getMaxStationNameLength(){
    var resol = resolution;
    if (resol > 400) { resol = 400; }
    if (resol < 340) { resol -= 100; }
    var ratio = 400/26;
    return parseInt(resol/ratio);
}

function cutText(text){
    var out;
    if (text.length > getMaxStationNameLength() ) {
        out  = document.createTextNode(text.slice(0,getMaxStationNameLength()-3) + "...");
    } else {
        out = document.createTextNode(text);;
    }
    return out;
}


var playingNumber = null;
function load() {
    console.log("STR MAX", getMaxStationNameLength())

    var response = httpGet("/radio/api/station/all");
    var responseJson = JSON.parse(response);
    Stations_List_Json = responseJson["value"];
    document.getElementById("STATIONS_LIST").innerHTML = "";
    var isPlayingSetted = false;
    for (var iter = 0; iter < Stations_List_Json.length; ++iter) {
        var item = document.createElement("LI");
        item.setAttribute("class", "Item");
        item.setAttribute("id", iter);
        item.style.backgroundColor = colors.col_station_card_background;
        item.style.color = colors.col_station_name;
        var station_radio_img = document.createElement("img");
        station_radio_img.setAttribute("src", "/radio/res/img/player_radio.png")
        station_radio_img.setAttribute("class", "Station_radio_img")
        
        var station_play_btn = document.createElement("BUTTON");
        station_play_btn.setAttribute("class", "Station_play_btn");
        station_play_btn.setAttribute("id", iter);
        station_play_btn.setAttribute("onclick", "set_station(this.id)");
        
        if (Stations_List_Json[iter]["isPlaying"]) {
            playingNumber = iter;
            isPlayingSetted = true;
            station_radio_img.style.filter = colors.col_station_radio_img_playing;
            station_play_btn.style.backgroundImage = 'url("/radio/res/img/playing.png")';            
            station_play_btn.style.filter = colors.col_station_playing;
        } else {
            station_play_btn.style.backgroundImage = 'url("/radio/res/img/play.png")';
            station_play_btn.style.filter = colors.col_station_play;
            station_radio_img.style.filter = colors.station_radio_img;
        }      
        if (!isPlayingSetted){
            playingNumber = null;
        }
        item.appendChild(station_radio_img)
        item.appendChild(cutText(Stations_List_Json[iter]["name"]));
        item.appendChild(station_play_btn);
        document.getElementById("STATIONS_LIST").appendChild(item);    
    }
}         
    
function set_station(id) {
    if (playingNumber != null && playingNumber == id) {
        var replyPlay = httpGet("/radio/api/audio/stop");
    } else {
        var bodyJson = JSON.parse('{"name": ""}');
        console.log("LOG", id);
        console.log("HERE", Stations_List_Json[id]["name"]);
        bodyJson["name"] = Stations_List_Json[id]["name"];
        console.log(bodyJson)
        var replySet = httpPost("/radio/api/audio/set", JSON.stringify(bodyJson));
        console.log(replySet)
        var replyPlay = httpGet("/radio/api/audio/play");
        console.log(replyPlay)
    }
    reload();
}

function load_player_state(){
    var player = document.getElementById("Player_footer");
    var stateBtn = document.getElementById("button_state_img");
    document.getElementById("Player_head").innerHTML = "";
    var PlayerList = document.getElementById("Player_head");

    var title = document.createElement("li");
    title.setAttribute("id", "Player_title");
    title.style.color = colors.col_player_title;
    var title_img = document.createElement("img");
    title_img.setAttribute("class", "Player_img");
    title_img.src = "radio/res/img/player_title.png";
    title_img.style.filter = colors.col_player_img;
    title.appendChild(title_img);

    var name = document.createElement("li");
    name.setAttribute("id", "Player_name");
    name.style.color = colors.col_player_name;
    var name_img = document.createElement("img");
    name_img.setAttribute("class", "Player_img");
    name_img.src = "radio/res/img/player_radio.png";
    name_img.style.filter = colors.col_player_img;
    name.appendChild(name_img);

    var state = JSON.parse(httpGet("/radio/api/audio/state"))["value"]["state"];
    var current = JSON.parse(httpGet("/radio/api/audio/get/station"));
    if (current["code"] == 200){
        current = current["value"];
        name.appendChild(cutText(current["name"]));
        if (current["title"].length == 0) {current["title"] = "title";}
        title.appendChild(cutText(current["title"]));
    } else {
        name.appendChild(document.createTextNode("station"));
        title.appendChild(document.createTextNode("title"));
    }

    if (state == "play") {
        stateBtn.src = stop_img;
        stateBtn.style.filter = colors.col_player_play;
    } else {
        stateBtn.src = play_img;
        stateBtn.style.filter = colors.col_player_stop;    
    }

    PlayerList.appendChild(name);
    PlayerList.appendChild(title);

}

function change_state(){
    if (DEBUG) {console.log("CHANGE STATE");}
    var state = JSON.parse(httpGet("/radio/api/audio/state"))["value"]["state"];
    if (state == "play"){ 
        httpGet("/radio/api/audio/stop");
    } else {
        httpGet("/radio/api/audio/play");
    }
    reload(); 
}

function httpGet(theUrl)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open( "GET", theUrl, false ); // false for synchronous request
    xmlHttp.send( null );
    return xmlHttp.responseText;
}

function httpPost(theUrl, body)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open( "POST", theUrl, false ); // false for synchronous request
    xmlHttp.send( body );
    return xmlHttp.responseText;
}
