window.onload = function() {
    displayAll();
};

setInterval(function() {

}, 5000);

setInterval(function() {
    if (!PAGE_VOLUME_BLOCK && PAGE_VOLUME) {
        PAGE_VOLUME = false;
        displayPage();
    }
    PAGE_VOLUME_BLOCK = false;
}, 5000);

STATIONS_LIST = []

/* ANCHOR FLAGS */
var MODE_DELETE = false;
var MODE_VIEW_URL = false;
var PAGE_NEW = false;
var PAGE_VOLUME = false;
var PAGE_VOLUME_BLOCK = false;
var PLAYER_isPlaying = false;

function flagsDefault() {
    MODE_DELETE = false;
    MODE_VIEW_URL = false;
    PAGE_NEW = false;
    PLAYER_isPlaying = false;
}

/* 
    ANCHOR on click signals ######################
*/

function onClickCheck(id) {
    requestForStationSetReturnBool(STATIONS_LIST[id].name);
    requestForPlayReturnBool();
    displayAll();
}

function onClickUncheck() {
    onClickStop();
}

function onClickDeletePage() {
    MODE_DELETE = !MODE_DELETE;
    displayPage();
}

function onClickDelete(id) {
    requestForStationDeleteReturnBool(STATIONS_LIST[id].name);
    displayAll();
}

function onClickStop() {
    requestForStopReturnBool();
    displayAll();
}

function onClickView() {
    MODE_VIEW_URL = !MODE_VIEW_URL;
    displayPage();
}

function onClickNew() {
    PAGE_NEW = !PAGE_NEW;
    displayPage();
}

function onClickNewAdd() {
    var name = document.getElementById("ContentNewStationNameInput").value;
    var uri = document.getElementById("ContentNewStationUriInput").value;
    if (requestForStationAddReturnBool(name, uri)) {
        alert("New station: " + name + "  " + uri);
    }
    PAGE_NEW = false;
    displayPage();
}

function onClickNewClear() {
    document.getElementById("ContentNewStationNameInput").value = "";
    document.getElementById("ContentNewStationUriInput").value = "";
    PAGE_NEW = false;
    displayPage();
}


/* TODO onClickCheckFavourite */
/* TODO onClickFavourites */

function onClickPlay() {
    requestForPlayReturnBool();
    displayAll();
}

function onClickNext() {
    requestForNextReturnBool();
    requestForPlayReturnBool();
    displayAll();
}

function onClickPrev() {
    requestForPrevReturnBool();
    requestForPlayReturnBool();
    displayAll();
}

function onClickVolume() {
    PAGE_VOLUME = !PAGE_VOLUME;
    var volume = requestForVolumeLevelReturnInt();
    document.getElementById("volumeControl").value = volume;
    displayPage();
}

function onClickSetVolume(volume) {
    volume = parseInt(volume);
    PAGE_VOLUME_BLOCK = true;
    if (volume >= 0 && volume <= 100) {
        requestForVolumeSetLevelReturnBool(volume);
    }
}

/* 
    ANCHOR Display content ########################
*/

function displayAll() {
    displayPage();
    displayPlayer();
}

function displayPage() {
    if (PAGE_VOLUME) {
        displayVolume();
    }
    else if (PAGE_NEW) {
        document.getElementById("ContentNewStationContainer").style.display = "inline";
        document.getElementById("ContentStationsListContainer").style.display = "none";
        document.getElementById("volumeControl").style.display = "none";
    } else {
        document.getElementById("ContentStationsListContainer").style.display = "inline";
        document.getElementById("ContentNewStationContainer").style.display = "none";
        document.getElementById("volumeControl").style.display = "none";
        var htmlStationList = document.getElementById("ContentStationList");
        htmlStationList.innerHTML = "";
        var stationsList = requestForStationsListReturnArray();
        for (var id = 0; id < stationsList.length; ++id) {
            var card = getNewCard(stationsList[id], id);
            htmlStationList.appendChild(card);
        }
    }
}

function displayPlayer() {
    var status = requestForStatusReturnBool();
    var station = requestForStationReturnStation();
    PLAYER_isPlaying = status;
    if (PLAYER_isPlaying) {
        document.getElementById("FooterState").src = "radio/res/img/stop.png";
        document.getElementById("FooterState").setAttribute("onclick", "onClickStop()");
    } else {
        document.getElementById("FooterState").src = "radio/res/img/play.png";
        document.getElementById("FooterState").setAttribute("onclick", "onClickPlay()");
    }
    if (station.name.length > 0) {
        document.getElementById("FooterStationNameText").innerText = station.name;
        document.getElementById("FooterStationTitleText").innerText = station.title;
    } else {
        document.getElementById("FooterStationNameText").innerText = "Station not checked!";
        document.getElementById("FooterStationTitleText").innerText = "Please, click choosen station to play radio.";
    }
}

function displayVolume() {
    document.getElementById("ContentStationsListContainer").style.display = "none";
    document.getElementById("ContentNewStationContainer").style.display = "none";
    document.getElementById("volumeControl").style.display = "inline";
}

/* TODO displayDelete */
/* TODO displayUrl */
/* TODO displayVolume */


/* 
    ANCHOR Get new objects ####################
*/

function getNewCard(station, id) {
    var card = document.createElement("li");
    card.setAttribute("class", "ContentStationCard");

    var devLeft = document.createElement("div");
    devLeft.setAttribute("class", "cardRadioLeft");
        var devLeftImg = document.createElement("img");
            devLeftImg.setAttribute("class", "cardRadioImgSmall");
            devLeftImg.src = "radio/res/img/radio.png";
        devLeft.appendChild(devLeftImg);
        if (!MODE_VIEW_URL) {
            var devLeftP = document.createElement("p");
                devLeftP.setAttribute("class", "cardRadioText");
                devLeftP.innerText = station.name;
            devLeft.appendChild(devLeftP);
        } else {
            var devLeftInput = document.createElement("input");
                devLeftInput.setAttribute("class", "cardRadioText");
                devLeftInput.value = station.uri;
            devLeft.appendChild(devLeftInput);
        }
    card.appendChild(devLeft);

    var devRight = document.createElement("div");
    devRight.setAttribute("class", "cardRadioRight");
        var devRightImgFav = document.createElement("img"); // TODO FAVOURITE
            devRightImgFav.setAttribute("id", id);
            devRightImgFav.setAttribute("class", "cardFavouriteImgSmall");
            devRightImgFav.src = "radio/res/img/favourite_full_love.png";
        devRight.appendChild(devRightImgFav)
        var devRightImgCheck = document.createElement("img");
            devRightImgCheck.setAttribute("id", id);
            devRightImgCheck.setAttribute("class", "cardCheckImgSmall");
            if (!MODE_DELETE) {
                if (station.isPlaying) {
                    devRightImgCheck.src = "radio/res/img/check.png";
                    devRightImgCheck.setAttribute("onclick", "onClickUncheck()");
                } else {
                    devRightImgCheck.src = "radio/res/img/uncheck.png";
                    devRightImgCheck.setAttribute("onclick", "onClickCheck(this.id)");
                }
            } else {
                devRightImgCheck.src = "radio/res/img/delete_forever.png";
                devRightImgCheck.setAttribute("onclick", "onClickDelete(this.id)");
            }
        devRight.appendChild(devRightImgCheck);
    card.appendChild(devRight);

    return card;
}


/* 
    ANCHOR Request for ########################
*/

function requestForStationsListReturnArray() {
    var stationsList = httpGet("/radio/api/station/all");
    var stationsListJSON = JSON.parse(stationsList);
    stationsListJSON = stationsListJSON["value"];
    STATIONS_LIST = [];
    if (stationsListJSON == null) return STATIONS_LIST;
    for (var iter = 0; iter < stationsListJSON.length; ++iter) {
        STATIONS_LIST.push( new Station(
            stationsListJSON[iter]["name"],
            stationsListJSON[iter]["uri"],
            stationsListJSON[iter]["isPlaying"],
            stationsListJSON[iter]["title"]
            ));
    }
    return STATIONS_LIST;
}

function requestForStationReturnStation() {
    var station = httpGet("/radio/api/audio/get/station");
    var stationJSON = JSON.parse(station);
    stationJSON = stationJSON["value"];
    station = new Station(
        stationJSON["name"],
        stationJSON["uri"],
        stationJSON["isPlaying"],
        stationJSON["title"]
    )    
    return station;
}

function requestForStationAddReturnBool(name, uri) {
    var station = new Station(name, uri);
    var replySet = httpPost("/radio/api/station/put", station.getJsonStrNameAndUri());
    replySet = JSON.parse(replySet);
    var status = new Status(
        replySet["code"],
        replySet["message"]);
    return status.check();
}

function requestForStationDeleteReturnBool(name) {
    var station = new Station(name, null);
    var replySet = httpPost("/radio/api/station/delete", station.getJsonStrName());
    replySet = JSON.parse(replySet);
    var status = new Status(
        replySet["code"],
        replySet["message"]);
    return status.check();
}

function requestForStationSetReturnBool(name) {
    var station = new Station(name, null);
    var replySet = httpPost("/radio/api/audio/set", station.getJsonStrName());
    replySet = JSON.parse(replySet);
    var status = new Status(
        replySet["code"],
        replySet["message"]);
    return status.check();
}

function requestForStatusReturnBool() {
    var status = httpGet("/radio/api/audio/state");
    var statusJson = JSON.parse(status);
    statusJson = statusJson["value"];
    if (statusJson["state"] == "play") {return true;}
    return false;
}

function requestForPlayReturnBool() {
    var reply = httpGet("/radio/api/audio/play");
    reply = JSON.parse(reply);
    var status = new Status(
        reply["code"],
        reply["message"]);
    return status.check();
}

function requestForStopReturnBool() {
    var reply = httpGet("/radio/api/audio/stop");
    reply = JSON.parse(reply);
    var status = new Status(
        reply["code"],
        reply["message"]);
    return status.check();
}

function requestForNextReturnBool() {
    var reply = httpGet("/radio/api/audio/next");
    reply = JSON.parse(reply);
    var status = new Status(
        reply["code"],
        reply["message"]);
    return status.check();
}

function requestForPrevReturnBool() {
    var reply = httpGet("/radio/api/audio/prev");
    reply = JSON.parse(reply);
    var status = new Status(
        reply["code"],
        reply["message"]);
    return status.check();
}

function requestForVolumeLevelReturnInt() {
    var reply = httpGet("/radio/api/volume/get");
    reply = JSON.parse(reply);
    var status = new Status(
        reply["code"],
        reply["message"]);
    return reply["value"]["volume"];
}

function requestForVolumeSetLevelReturnBool(volume) {
    var volumeJson = JSON.parse('{"volume": "" }');
    volumeJson["volume"] = parseInt(volume);
    var reply = httpPost("/radio/api/volume/set", JSON.stringify(volumeJson));
    reply = JSON.parse(reply);
    var status = new Status(
        reply["code"],
        reply["message"]);
    return status.check();
}

/* 
    ANCHOR Models #############################
*/
class Station {
    constructor(name, uri, isPlaying=null, title=null) {
        this.name = name;
        this.uri = uri;
        this.isPlaying = isPlaying;
        this.title = title;
    }

    getJsonStrName(){
        var nameJson = JSON.parse('{"name": ""}');
        nameJson["name"] = this.name;
        return JSON.stringify(nameJson);
    }

    getJsonStrNameAndUri(){
        var nameAndUriJson = JSON.parse('{"name": "", "uri":""}');
        nameAndUriJson["name"] = this.name;
        nameAndUriJson["uri"] = this.uri;
        return JSON.stringify(nameAndUriJson);
    }
}

class Status {
    constructor(code, message) {
        this.code = code;
        this.message = message;
    }
    isOk() {
        if (this.code == 200) { return true; } 
        return false;
    }
    check() {
        if (!this.isOk()) { alert("Error! " + this.message); }
        return this.isOk();
    }
}

/* 
    ANCHOR Http requests #######################################
*/

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
