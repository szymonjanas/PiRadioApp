package main

import (
    "html/template"
    "net/http"
    "os"
    zmq "github.com/pebbe/zmq4"
)

var client *zmq.Socket
var checkedStation string = "none"
var DEBUG bool = true

type Message struct {
    Message string
    Type bool
}

var informMessage Message 

type StationsName struct {
    Name string
}

type StationsPageData struct {
    Stations []StationsName
}

type PlayingDetails struct {
    Station string
    Title string
    Url string
}

type ViewPageData struct {
    StationsData StationsPageData
    PlayingData PlayingDetails
    Msg Message
    State bool
}

func getStations() []StationsName {
    var stations []StationsName
    strStations := Comm.SendRequest("station get all")
    for i := range strStations {
        stations = append(stations, StationsName{strStations[i]})
    }
    return stations
}

/* 
    HANDLERS: api 
*/

func viewHandler(w http.ResponseWriter, r *http.Request){
    Log.Debug("main page")
    tmpl, err := template.ParseFiles("../server/resources/server.html")
    if err != nil {
        Log.Err("Error occure: " + err.Error())
        w.WriteHeader(http.StatusInternalServerError)
        return
    }
    
    current := Comm.SendRequest("station get current")
    var StateFlag bool = false
    StateChecker := Comm.SendRequest("isWorking")[0]
    Log.Warn("StateChecker: " + StateChecker)
    if  StateChecker == "working" {
        StateFlag = true
    } 
    details := ViewPageData {
        StationsData: StationsPageData{
            Stations: getStations(),
        },
        PlayingData: PlayingDetails {
            Station: current[0],
            Title: current[1],
            Url: current[2],
        },
        Msg: informMessage,
        State: StateFlag,
    }


    tmpl.Execute(w, details)
}

func playHandler(w http.ResponseWriter, r *http.Request){
    Comm.SendRequest("engine state set play")
    Log.Info("play ")
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func stopHandler(w http.ResponseWriter, r *http.Request){
    Comm.SendRequest("engine state set stop")
    Log.Info("stop")
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func prevHandler(w http.ResponseWriter, r *http.Request){
    Comm.SendRequest("station switch prev")
    Log.Info("prev")
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func nextHandler(w http.ResponseWriter, r *http.Request){
    Comm.SendRequest("station switch next")
    Log.Info("next")
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func setHandler(w http.ResponseWriter, r *http.Request){
    body := r.FormValue("Stations")
    checkedStation = body
    Log.Info("checked " + checkedStation)
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func submitHandler(w http.ResponseWriter, r *http.Request){
    Comm.SendRequest("station set " + checkedStation)
    Comm.SendRequest("engine state set play")
    Log.Info("submit " + checkedStation)
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func setsubmitHandler(w http.ResponseWriter, r *http.Request){
    body := r.FormValue("Stations")
    checkedStation = body
    Comm.SendRequest("station set " + checkedStation)
    Comm.SendRequest("engine state set play")
    Log.Info("checked and submit " + checkedStation)
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func removeHandler(w http.ResponseWriter, r *http.Request){
    Comm.SendRequest("station remove " + checkedStation)
    Log.Info("remove " + checkedStation)
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func addHandler(w http.ResponseWriter, r *http.Request){
    name := r.FormValue("stationName")
    uri := r.FormValue("stationUri")
    Comm.SendRequest("station new " + name + " " + uri)
    Log.Info("add new " + name + " " + uri)
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 



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
    http.HandleFunc("/radio/api/play", playHandler)
    http.HandleFunc("/radio/api/stop", stopHandler)
    http.HandleFunc("/radio/api/set", setHandler)
    http.HandleFunc("/radio/api/next", nextHandler)
    http.HandleFunc("/radio/api/prev", prevHandler)
    http.HandleFunc("/radio/api/submit", submitHandler)
    http.HandleFunc("/radio/api/setsubmit", setsubmitHandler)
    http.HandleFunc("/radio/api/remove", removeHandler)
    http.HandleFunc("/radio/api/add", addHandler)
    http.HandleFunc("/radio/", viewHandler)

    Log.Warn("serve uri: " + serveUri)
    errServe := http.ListenAndServe(serveUri, nil)
    if errServe != nil {
        Log.Err("error serve: " + errServe.Error()) 
    }
}
