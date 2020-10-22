
var text = '{ "value" : [' +
'{ "name":"John Some text "},' +
'{ "name":"Anna Looooo Texxxxkiiittt" },' +
'{ "name":"Peter aklsdlajfh hf oefmsaomf oe"} ]}';

var obj = JSON.parse(text);
var textList = obj["value"]

window.onload = function() {
    load();
  };

const interval = setInterval(function() {
    load();
  }, 5000);
 

function load() {
    document.getElementById("STATIONS_LIST").innerHTML = "";
    for (var iter = 0; iter < textList.length; ++iter) {
        console.log(textList[iter]["name"]);
        var item = document.createElement("LI");
        item.setAttribute("class", "Item");
        item.setAttribute("id", iter);
        item.appendChild(document.createTextNode(textList[iter]["name"]));
        console.log(item)
        document.getElementById("STATIONS_LIST").appendChild(item);    
    }
}         
    
function myFunction() {
  var node = document.createElement("LI");
  var textnode = document.createTextNode("Water");
  node.appendChild(textnode);
  document.getElementById("STATIONS_LIST").appendChild(node);
}














