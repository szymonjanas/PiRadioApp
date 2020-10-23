
var Stations_List_Json = [];

let STATION_LIST_MAX_WIDTH_pt = 400;
var resolution = window.screen.availWidth;
var play_img = "radio/res/img/play.png"
var stop_img = "radio/res/img/stop.png"

let DEBUG = true;

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
            station_radio_img.style.filter = "invert(45%) sepia(66%) saturate(845%) hue-rotate(310deg) brightness(90%) contrast(93%)";
            station_play_btn.style.backgroundImage = 'url("/radio/res/img/playing.png")';            
            station_play_btn.style.filter = "invert(45%) sepia(66%) saturate(845%) hue-rotate(310deg) brightness(90%) contrast(93%)";
        } else {
            station_play_btn.style.backgroundImage = 'url("/radio/res/img/play.png")';
            station_play_btn.style.filter = "invert(78%) sepia(48%) saturate(625%) hue-rotate(353deg) brightness(88%) contrast(95%)";
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



function button_state(){

    var Station; 
    var btn_img = document.getElementById("button_state_img");
    var title = document.getElementById("Player_title");
    var name = document.getElementById("Player_name");

    if (playingNumber != null){ 
        Station = Stations_List_Json[playingNumber];
        console.log("Station", Station["name"]);
        title.textContent = Station["title"];
        name.textContent = Station["name"];
        if (Station["isPlaying"]) {
            btn_img.src = stop_img;
            btn_img.style.filter = "invert(45%) sepia(66%) saturate(845%) hue-rotate(310deg) brightness(90%) contrast(93%)";
        } else {
            btn_img.src = play_img;
            btn_img.style.filter = "invert(64%) sepia(9%) saturate(2912%) hue-rotate(14deg) brightness(93%) contrast(85%)";    
        }
    } else {
        title.textContent = "title";
        btn_img.src = play_img;
        btn_img.style.filter = "invert(64%) sepia(9%) saturate(2912%) hue-rotate(14deg) brightness(93%) contrast(85%)";    
    }
}

function load_player_state(){
    var player = document.getElementById("Player_footer");
    var stateBtn = document.getElementById("button_state_img");
    document.getElementById("Player_head").innerHTML = "";
    var PlayerList = document.getElementById("Player_head");

    var title = document.createElement("li");
    title.setAttribute("id", "Player_title");
    var title_img = document.createElement("img");
    title_img.setAttribute("class", "Player_img");
    title_img.src = "radio/res/img/player_title.png";
    title.appendChild(title_img);

    var name = document.createElement("li");
    name.setAttribute("id", "Player_name");
    var name_img = document.createElement("img");
    name_img.setAttribute("class", "Player_img");
    name_img.src = "radio/res/img/player_radio.png";
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
        stateBtn.style.filter = "invert(45%) sepia(66%) saturate(845%) hue-rotate(310deg) brightness(90%) contrast(93%)";
    } else {
        stateBtn.src = play_img;
        stateBtn.style.filter = "invert(64%) sepia(9%) saturate(2912%) hue-rotate(14deg) brightness(93%) contrast(85%)";    
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
