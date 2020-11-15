
var Header_title_text = document.getElementById("Header_title_text");

var Header_add_img = document.getElementById("Header_add_img");
var Header_delete_img = document.getElementById("Header_delete_img");
var Header_url_img = document.getElementById("Header_url_img");

var Footer_play_img = document.getElementById("Footer_play_img");
var Footer_stop_img = document.getElementById("Footer_stop_img");
var Footer_prev_img = document.getElementById("Footer_prev_img");
var Footer_next_img = document.getElementById("Footer_next_img");

var Footer_volume_button_img = document.getElementById("Footer_volume_button_img");
var Footer_volume_value = document.getElementById("Footer_volume_value");
var Footer_volume_up_img = document.getElementById("Footer_volume");
var Footer_volume_down_img = document.getElementById("Footer_volume_down_img");

var Footer_station_title_text = document.getElementById("Footer_station_title_text");
var Footer_station_name_text = document.getElementById("Footer_station_name_text");

function load_stations(){
    console.log("Load stations!");
    var Stations_List = (JSON.parse(httpGet("/radio/api/station/all")))["value"];


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
