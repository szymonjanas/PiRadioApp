package main

import (
    "net/http"
    "os"
    "encoding/json"
    "io/ioutil"
    "fmt"
    zmq "github.com/pebbe/zmq4"
)

type Station struct {
    Name string `json:"name"`
    Uri string `json:"uri"`
}

type StationName struct {
    Name string `json:"name"`
}

type Message struct {
    Type string `json:"type"`
    Message string `json:"message"`
    Value []Station `json:"value"`
}

/*
    Internal communication
*/
var checkedStation string

var client *zmq.Socket
func SendRequest(request string) string {
    /*
        send request; recive, decode and return reply
    */
    (*client).SendMessage(request, 0)
    Log.Info("send request: " + request)
    msg, err := (*client).RecvMessage(0)
    if err != nil {
        Log.Err("send error: " + err.Error())
    }
    reply := msg[0]
    Log.Info("recive replay: " + reply)
    return reply 
}

/* 
    HANDLERS: api 
*/

func viewHandler(w http.ResponseWriter, r *http.Request){
    fmt.Fprintf(w, "Welcome to the HomePage!")
}

func getAllHandler(w http.ResponseWriter, r *http.Request){
    all := SendRequest("station get all")
    var msg Message
    if err := json.Unmarshal([]byte(all), &msg); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(msg); err != nil {
		Log.Err(err.Error())
	}
}

func playHandler(w http.ResponseWriter, r *http.Request){
    SendRequest("engine state set play")
    Log.Info("play ")
} 

func stopHandler(w http.ResponseWriter, r *http.Request){
    SendRequest("engine state set stop")
    Log.Info("stop")
} 

func prevHandler(w http.ResponseWriter, r *http.Request){
    SendRequest("station switch prev")
    Log.Info("prev")
} 

func nextHandler(w http.ResponseWriter, r *http.Request){
    SendRequest("station switch next")
    Log.Info("next")
} 

func setHandler(w http.ResponseWriter, r *http.Request){
    reqBody, _ := ioutil.ReadAll(r.Body)
    var msg StationName
    if err := json.Unmarshal([]byte(reqBody), &msg); err != nil {
        Log.Err(err.Error())
    }
    checkedStation = msg.Name
    rep := SendRequest("station set " + checkedStation)
    Log.Info("checked and submit: " + checkedStation)
    var repMsg Message
    if err := json.Unmarshal([]byte(rep), &repMsg); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(repMsg); err != nil {
		Log.Err(err.Error())
    }
}

func removeHandler(w http.ResponseWriter, r *http.Request){
    reqBody, _ := ioutil.ReadAll(r.Body)
    var msg StationName
    if err := json.Unmarshal([]byte(reqBody), &msg); err != nil {
        Log.Err(err.Error())
    }
    rep := SendRequest("station remove " + msg.Name)
    Log.Info("station removed: " + msg.Name)
    var repMsg Message
    if err := json.Unmarshal([]byte(rep), &repMsg); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(repMsg); err != nil {
		Log.Err(err.Error())
    }
} 

func putHandler(w http.ResponseWriter, r *http.Request){
    reqBody, _ := ioutil.ReadAll(r.Body)
    var msg Station
    if err := json.Unmarshal([]byte(reqBody), &msg); err != nil {
        Log.Err(err.Error())
    }

    Log.Info("station put " + msg.Name + " " + msg.Uri)
    rep := SendRequest("station put " + msg.Name + " " + msg.Uri)

    var repMsg Message
    if err := json.Unmarshal([]byte(rep), &repMsg); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(repMsg); err != nil {
		Log.Err(err.Error())
    }
} 

/*
    MAIN
*/

func main() {

    args := os.Args[1:]

    engineUri := "ipc://piradio.app"
    serveUri := ":8080"
    resourcePath := "../server/resources/"

    for i := 0; i < len(args); i++ {
        if args[i] == "--cmd-colors" || args[i] == "-col" {
            ColorStatus = true
        } else if args[i] == "--basic-cmd" || args[i] == "-b" {
            Basic = true
        } else if args[i] == "--icomm-address" || args[i] == "-ic" {
            i++;
            engineUri = "tcp://" + args[i]
            Log.Warn("Setted uri: " + engineUri)
        } else if args[i] == "--icomm-port" || args[i] == "-icp" {
            i++;
            engineUri = "tcp://localhost:" + args[i]
            Log.Warn("Setted uri port: " + engineUri)
        } else if args[i] == "--host-address" || args[i] == "-h" {
            i++;
            serveUri = args[i]
            Log.Warn("Setted serve address: " + serveUri)
        } else if args[i] == "--host-port" || args[i] == "-hp" {
            i++;
            serveUri = ":" + args[i]
            Log.Warn("Setted serve port: " + serveUri)
        } else if args[i] == "--resource" || args[i] == "-res" {
            i++;
            resourcePath = args[i]
            Log.Warn("Setted resource path: " + resourcePath)
        } else if args[i] == "--debug" || args[i] == "-d" {
            
        }
    }

    socket, errSocket := zmq.NewSocket(zmq.PAIR)
    client = socket

    (*client).Connect(engineUri)
    if errSocket != nil {
        Log.Err("error socket: " + errSocket.Error())
    } else {
        Log.Warn("connected to server: " + engineUri)
    }
    
    http.Handle("/radio/res/", http.StripPrefix("/radio/res/", http.FileServer(http.Dir(resourcePath))))
    http.HandleFunc("/radio/api/station/all", getAllHandler)
    http.HandleFunc("/radio/api/state/play", playHandler)
    http.HandleFunc("/radio/api/state/stop", stopHandler)
    http.HandleFunc("/radio/api/station/set", setHandler)
    http.HandleFunc("/radio/api/station/next", nextHandler)
    http.HandleFunc("/radio/api/station/prev", prevHandler)
    http.HandleFunc("/radio/api/station/remove", removeHandler)
    http.HandleFunc("/radio/api/station/put", putHandler)
    http.HandleFunc("/radio", viewHandler)

    Log.Warn("serve uri: " + serveUri)
    errServe := http.ListenAndServe(serveUri, nil)
    if errServe != nil {
        Log.Err("error serve: " + errServe.Error()) 
    }
}
