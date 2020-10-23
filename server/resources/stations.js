
var Stations_List_Json = [];

window.onload = function() {
    load();
};

setInterval(function() {
    load();
}, 50000);

var strMaxLength = 22;

function load() {
    var response = httpGet("/radio/api/station/all");
    var responseJson = JSON.parse(response);
    Stations_List_Json = responseJson["value"];
    document.getElementById("STATIONS_LIST").innerHTML = "";
    for (var iter = 0; iter < Stations_List_Json.length; ++iter) {
        var item = document.createElement("LI");
        item.setAttribute("class", "Item");
        item.setAttribute("id", iter);

        var station_radio_img = document.createElement("img");
        station_radio_img.setAttribute("src", "/radio/res/img/player_radio.png")
        station_radio_img.setAttribute("class", "Station_radio_img")
        var nameStr = Stations_List_Json[iter]["name"];
        var name = "";
        if (nameStr.length > strMaxLength ) {
            name  = document.createTextNode(nameStr.slice(0,strMaxLength-3) + "...");
        } else {
            name = document.createTextNode(nameStr);;
        }

        var station_play_btn = document.createElement("BUTTON");
        station_play_btn.setAttribute("class", "Station_play_btn");
        station_play_btn.setAttribute("id", iter);
        station_play_btn.setAttribute("onclick", "set_station(this.id)");

        if (Stations_List_Json[iter]["isPlaying"]) {
            station_radio_img.style.filter = "invert(45%) sepia(66%) saturate(845%) hue-rotate(310deg) brightness(90%) contrast(93%)";
            station_play_btn.style.backgroundImage = 'url("/radio/res/img/playing.png")';            
            station_play_btn.style.filter = "invert(45%) sepia(66%) saturate(845%) hue-rotate(310deg) brightness(90%) contrast(93%)";
        } else {
            station_play_btn.style.backgroundImage = 'url("/radio/res/img/play.png")';
            station_play_btn.style.filter = "invert(78%) sepia(48%) saturate(625%) hue-rotate(353deg) brightness(88%) contrast(95%)";
        }      
        item.appendChild(station_radio_img)
        item.appendChild(name);
        item.appendChild(station_play_btn);
        document.getElementById("STATIONS_LIST").appendChild(item);    
    }
}         
    
function set_station(id) {
    
    var bodyJson = JSON.parse('{"name": ""}');
    console.log("LOG", id);
    console.log("HERE", Stations_List_Json[id]["name"]);
    bodyJson["name"] = Stations_List_Json[id]["name"];
    console.log(bodyJson)
    var replySet = httpPost("/radio/api/audio/set", JSON.stringify(bodyJson));
    console.log(replySet)
    var replyPlay = httpGet("/radio/api/audio/play");
    console.log(replyPlay)
    load();
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
