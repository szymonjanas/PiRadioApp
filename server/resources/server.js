
var Stations_List_Json = [];

let STATION_LIST_MAX_WIDTH_pt = 400;
var resolution = window.screen.availWidth;
var play_img = "radio/res/img/play.png"
var stop_img = "radio/res/img/stop.png"

let DEBUG = true;

/*
ANCHOR

########################
####### COLORS #########
########################

*/
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
        this.col_player_next;
        this.col_player_prev;
        this.col_player_img;
        this.col_player_name;
        this.col_player_title;
        this.col_player_background;
        this.col_player_border;

        this.add_button_submit;  
        this.add_button_clear;

        this.col_delete_button;

        this.col_view_button;
    }
};

var language = class Language {
    constructor(){
        this.add_name_placeholder;
        this.add_uri_placeholder;
        this.add_button_submit;
        this.add_button_clear;
        this.add_wrong_data_warning;
    }
}

function load_language(){
    language.add_name_placeholder = "Name...";
    language.add_uri_placeholder = "Url...";
    language.add_button_submit = "Submit";
    language.add_button_clear = "Clear";
    language.add_wrong_data_warning = "Error! Wrong 'name' or 'url' given!";
}

var add_station_history = class AddStationHistory{
    constructor() {
        this.station;
        this.uri;
    }
};

function load_add_station_history() {
    add_station_history.station = "";
    add_station_history.uri = "";
}

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

    colors.add_button_submit = "#0D5C23";  
    colors.add_button_clear = "#90343E";

    colors.col_player_next = "invert(49%) sepia(89%) saturate(630%) hue-rotate(352deg) brightness(90%) contrast(99%)";
    colors.col_player_prev = colors.col_player_next;

    colors.col_delete_button = "invert(16%) sepia(87%) saturate(6103%) hue-rotate(355deg) brightness(94%) contrast(106%)";

    colors.col_view_button = "invert(20%) sepia(81%) saturate(1673%) hue-rotate(206deg) brightness(86%) contrast(90%)";

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

/*
ANCHOR 

###########################
####### COLORS END ######## 
###########################

*/

window.onload = function() {
    document.getElementById("LIST").style.width = resolution + "px";
    load_add_station_history();
    reload();
};

function reload() {
    load_language();
    load_colors();
    load_stations_list();
    load_player_state();
}
var block = false;
setInterval(function() {
    if (!block) {
        load_player_state();
    }
}, 5000);

function getMaxStationNameLength(min = 800){
    var resol = resolution; 
    if (resol > min) { resol = min; }
    else if (resol <= 320) { resol -= 100; }
    var ratio = 400/26;
    return parseInt(resol/ratio);
}

function cutText(text, min = 800){
    var out;
    if (text.length > getMaxStationNameLength(min) ) {
        out  = document.createTextNode(text.slice(0,getMaxStationNameLength(min)-3) + "...");
    } else {
        out = document.createTextNode(text);;
    }
    return out;
}

/*
ANCHOR
################################################################

*/

var playingNumber = null;
function load_stations_list(deleteStatus = false) {
    console.log("STR MAX", getMaxStationNameLength())
    document.getElementById("button_add_img").style.filter = colors.col_player_stop; 

    var response = httpGet("/radio/api/station/all");
    var responseJson = JSON.parse(response);
    Stations_List_Json = responseJson["value"];
    document.getElementById("STATIONS_LIST").innerHTML = "";
    var isPlayingSetted = false;
    if (Stations_List_Json == null){return;}
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

        if (deleteStatus) {
            station_radio_img.style.filter = colors.col_delete_button;
            station_play_btn.style.backgroundImage = 'url("/radio/res/img/delete_forever.png")';            
            station_play_btn.style.filter = colors.col_delete_button;
            station_play_btn.setAttribute("onclick", "delete_station(this.id)");

        } else {
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
        }
        item.appendChild(station_radio_img)
        if (view_url){
            item.appendChild(cutText(Stations_List_Json[iter]["uri"]));
        } else {
            item.appendChild(cutText(Stations_List_Json[iter]["name"]));
        }
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
    document.getElementById("button_add_img").style.filter = colors.col_player_stop; 
    document.getElementById("button_del_img").style.filter = colors.col_player_play;
    document.getElementById("button_next_img").style.filter = colors.col_player_next;
    document.getElementById("button_prev_img").style.filter = colors.col_player_prev;
    document.getElementById("button_view_img").style.filter = colors.col_view_button;

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
        name.appendChild(cutText(current["name"], 321));
        if (current["title"].length == 0) {current["title"] = "title";}
        title.appendChild(cutText(current["title"], 340));
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

var reveal_add = false;
function load_add_station() {
    deleteLoad = false;
    if (!reveal_add){
    block = true;
    reveal_add = true;   
    document.getElementById("button_add_img").style.filter = colors.col_player_play; 
    document.getElementById("button_del_img").style.filter = colors.col_player_play;
    document.getElementById("STATIONS_LIST").innerHTML = "";
    var list = document.getElementById("STATIONS_LIST");    

    var name = document.createElement("LI");
    var uri = document.createElement("LI");
    name.setAttribute("id", "add_name");
    name.setAttribute("class", "Item");
    name.style.backgroundColor = colors.col_station_card_background;
    uri.setAttribute("id", "add_uri");
    uri.setAttribute("class", "Item");
    uri.style.backgroundColor = colors.col_station_card_background;
    
    var nameInput = document.createElement("INPUT");
    nameInput.setAttribute("type", "text");
    nameInput.setAttribute("id", "add_station_name");
    nameInput.setAttribute("class", "add_input");
    nameInput.setAttribute("autocomplete", "off");
    nameInput.setAttribute("placeholder", language.add_name_placeholder);
    nameInput.style.borderColor = colors.col_player_name;
    nameInput.style.color = colors.col_player_title;
    nameInput.value = add_station_history.station;
    name.appendChild(nameInput);

    var uriInput = document.createElement("INPUT");
    uriInput.setAttribute("type", "text");
    uriInput.setAttribute("id", "add_station_uri");
    uriInput.setAttribute("class", "add_input");
    uriInput.setAttribute("placeholder", language.add_uri_placeholder);
    uriInput.style.borderColor = colors.col_player_name;
    uriInput.style.color = colors.col_player_title;
    uriInput.value = add_station_history.uri;
    uriInput.setAttribute("autocomplete", "off");
    uri.appendChild(uriInput);

    var buttons = document.createElement("LI");
    buttons.setAttribute("id", "buttons_add_rm");
    buttons.setAttribute("class", "Item");

    var add = document.createElement("BUTTON");
    add.setAttribute("id", "button_add_add");
    add.setAttribute("class", "Button_add");
    add.setAttribute("type", "button");
    add.setAttribute("onclick", "add_button_add()");
    add.textContent = language.add_button_submit;
    add.style.background = colors.add_button_submit;

    var clear = document.createElement("BUTTON");
    clear.setAttribute("id", "button_add_cancel");
    clear.setAttribute("class", "Button_add");
    clear.setAttribute("type", "button");
    clear.textContent = language.add_button_clear;
    clear.setAttribute("onclick", "add_button_clear()");
    clear.style.background = colors.add_button_clear;

    buttons.appendChild(clear);
    buttons.appendChild(add);

    list.appendChild(name);
    list.appendChild(uri);
    list.appendChild(buttons);

    } else {
        block = false;
        document.getElementById("button_add_img").style.filter = colors.col_player_stop; 
        if (document.getElementById("add_station_name").value == null) {add_station_history.station = "";}
        else { add_station_history.station = document.getElementById("add_station_name").value; }
        if (document.getElementById("add_station_uri").value == null) { add_station_history.uri = "";}
        else { add_station_history.uri  = document.getElementById("add_station_uri").value; }
        reveal_add = false;
        reload();
    }
}   

function add_button_clear(){
    add_station_history.station = "";
    add_station_history.uri = "";
    document.getElementById("add_station_name").value = add_station_history.station;
    document.getElementById("add_station_uri").value = add_station_history.uri;
}

function add_button_add(){
    var station_name = document.getElementById("add_station_name");
    var station_uri = document.getElementById("add_station_uri");
    if (station_name.value == null || station_uri.value == null ||
        station_name.value.length == 0 || station_uri.value.length == 0) {
        alert(language.add_wrong_data_warning)
        return;
    }
    var bodyJson = JSON.parse('{"name": "", "uri": ""}');
    bodyJson["name"] = station_name.value;
    bodyJson["uri"] = station_uri.value;
    var replySet = JSON.parse(httpPost("/radio/api/station/put", JSON.stringify(bodyJson)));
    alert(replySet["message"]);
    add_button_clear();
}

var deleteLoad = false;
function load_delete_station(){
    reveal_add = false;
    if (!deleteLoad) {
        block = true;
        document.getElementById("button_del_img").style.filter = colors.col_delete_button;
        load_stations_list(true);
        deleteLoad = true;
    } else {
        document.getElementById("button_del_img").style.filter = colors.col_player_play;
        load_stations_list();
        deleteLoad = false;
        block = false;
    }
}

function delete_station(id){
    var nameJson = JSON.parse('{"name":""}');
    nameJson["name"] = Stations_List_Json[id]["name"];
    alert(nameJson);
    var reply = JSON.parse(httpPost("/radio/api/station/delete", JSON.stringify(nameJson)));
    alert(reply["message"]);
    deleteLoad = false;
    reload();
}

function next(){
    httpGet("/radio/api/audio/next");
    httpGet("/radio/api/audio/play");
    reload();
}

function prev(){
    httpGet("/radio/api/audio/prev");
    httpGet("/radio/api/audio/play");
    reload();
}

var view_url = false;
function view_url_station(){
    if (!view_url) {
        view_url = true;
        reload();
    } else {
        view_url = false;
        reload();
    }

}

/* ANCHOR HTTP REQUEST */

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
