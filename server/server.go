package main

import (
    "net/http"
    "os"
    "encoding/json"
    "io/ioutil"
    "fmt"
    zmq "github.com/pebbe/zmq4"
)

type StationToEngine struct {
    Name string `json:"name"`
    Uri string `json:"uri"`
}

type StationFromEngine struct {
    Name string `json:"name"`
    Uri string `json:"uri"`
    IsPlaying bool `json:"isPlaying"`    
    Title string `json:"title"`
}

type MessageToServer struct {
    Route string `json:"route"`
    Value string `json:"value"`
}

type MessageFromServer struct {
    Code int `json:"code"`
    Message string `json:"message"`
    Value string `json:"value"`
}

type StationName struct {
    Name string `json:"name"`
}

type StationsArray struct {
    Stations []StationFromEngine
}

type PlayingState struct {
    State string `json:"state"`
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
    type MessageFromServerArr struct {
        Code int `json:"code"`
        Message string `json:"message"`
        Value []StationFromEngine `json:"value"`
    }
    var request MessageToServer
    request.Route = "database/get/all"
    request.Value = ""
    reqJson, _ := json.Marshal(request)
    got := SendRequest(string(reqJson))
    var reply MessageFromServerArr
    if err := json.Unmarshal([]byte(got), &reply); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(reply); err != nil {
		Log.Err(err.Error())
	}
}

func getCurrentHandler(w http.ResponseWriter, r *http.Request){
    type MessageFromServerCurr struct {
        Code int `json:"code"`
        Message string `json:"message"`
        Value StationFromEngine `json:"value"`
    }
    var request MessageToServer
    request.Route = "audio/get/current"
    request.Value = ""
    reqJson, _ := json.Marshal(request)
    got := SendRequest(string(reqJson))
    var reply MessageFromServerCurr
    if err := json.Unmarshal([]byte(got), &reply); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(reply); err != nil {
		Log.Err(err.Error())
	}
}

func playHandler(w http.ResponseWriter, r *http.Request){
    var state PlayingState 
    state.State = "play"
    stateJson, _ := json.Marshal(state)
    var request MessageToServer
    request.Route = "audio/set/state"
    request.Value = string(stateJson)
    requestJson, _ := json.Marshal(request)
    got := SendRequest(string(requestJson))
    var reply MessageFromServer
    if err := json.Unmarshal([]byte(got), &reply); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(reply); err != nil {
		Log.Err(err.Error())
	}
} 

func stopHandler(w http.ResponseWriter, r *http.Request){
    var state PlayingState 
    state.State = "stop"
    stateJson, _ := json.Marshal(state)
    var request MessageToServer
    request.Route = "audio/set/state"
    request.Value = string(stateJson)
    requestJson, _ := json.Marshal(request)
    got := SendRequest(string(requestJson))
    var reply MessageFromServer
    if err := json.Unmarshal([]byte(got), &reply); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(reply); err != nil {
		Log.Err(err.Error())
	}
} 

func prevHandler(w http.ResponseWriter, r *http.Request){
    var request MessageToServer
    request.Route = "audio/switch/prev"
    request.Value = ""
    requestJson, _ := json.Marshal(request)
    got := SendRequest(string(requestJson))
    var reply MessageFromServer
    if err := json.Unmarshal([]byte(got), &reply); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(reply); err != nil {
		Log.Err(err.Error())
	}
} 

func nextHandler(w http.ResponseWriter, r *http.Request){
    var request MessageToServer
    request.Route = "audio/switch/next"
    request.Value = ""
    requestJson, _ := json.Marshal(request)
    got := SendRequest(string(requestJson))
    var reply MessageFromServer
    if err := json.Unmarshal([]byte(got), &reply); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(reply); err != nil {
		Log.Err(err.Error())
	}
} 

func stateHandler(w http.ResponseWriter, r *http.Request){
    type MessageFromServerState struct {
        Code int `json:"code"`
        Message string `json:"message"`
        Value PlayingState `json:"value"`
    }
    var request MessageToServer
    request.Route = "audio/get/state"
    request.Value = ""
    requestJson, _ := json.Marshal(request)
    got := SendRequest(string(requestJson))
    var reply MessageFromServerState
    if err := json.Unmarshal([]byte(got), &reply); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(reply); err != nil {
		Log.Err(err.Error())
	}
} 

func setHandler(w http.ResponseWriter, r *http.Request){
    reqBody, _ := ioutil.ReadAll(r.Body)
    var name StationName
    if err := json.Unmarshal([]byte(reqBody), &name); err != nil {
        Log.Err(err.Error())
    }
    nameJson, _ := json.Marshal(name)
    var request MessageToServer
    request.Route = "audio/set/station"
    request.Value = string(nameJson)
    requestJson, _ := json.Marshal(request)
    replay := SendRequest(string(requestJson))
    var replayMessage MessageFromServer
    if err := json.Unmarshal([]byte(replay), &replayMessage); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(replayMessage); err != nil {
		Log.Err(err.Error())
    }
}

func deleteHandler(w http.ResponseWriter, r *http.Request){
    reqBody, _ := ioutil.ReadAll(r.Body)
    var name StationName
    if err := json.Unmarshal([]byte(reqBody), &name); err != nil {
        Log.Err(err.Error())
    }
    nameJson, _ := json.Marshal(name)
    var request MessageToServer
    request.Route = "database/delete"
    request.Value = string(nameJson)
    requestJson, _ := json.Marshal(request)
    replay := SendRequest(string(requestJson))
    var replayMessage MessageFromServer
    if err := json.Unmarshal([]byte(replay), &replayMessage); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(replayMessage); err != nil {
		Log.Err(err.Error())
    }
} 

func putHandler(w http.ResponseWriter, r *http.Request){
    reqBody, _ := ioutil.ReadAll(r.Body)
    var station StationToEngine
    if err := json.Unmarshal([]byte(reqBody), &station); err != nil {
        Log.Err(err.Error())
    }
    stationJson, _ := json.Marshal(station)
    var request MessageToServer
    request.Route = "database/put"
    request.Value = string(stationJson)
    requestJson, _ := json.Marshal(request)
    replay := SendRequest(string(requestJson))
    var replayMessage MessageFromServer
    if err := json.Unmarshal([]byte(replay), &replayMessage); err != nil {
        Log.Err(err.Error())
    }
    w.Header().Set("Content-Type", "application/json; charset=UTF-8")
    if err := json.NewEncoder(w).Encode(replayMessage); err != nil {
		Log.Err(err.Error())
    }
} 

/*
    MAIN
*/

func main() {

    args := os.Args[1:]

    engineUri := "tcp://127.0.0.1:7982"
    serveUri := ":8080"
    resourcePath := "../server/resources/"

    for i := 0; i < len(args); i++ {
        if args[i] == "--cmd-colors" || args[i] == "-col" {
            ColorStatus = true
        } else if args[i] == "--basic-cmd" || args[i] == "-b" {
            Basic = true
        } else if args[i] == "--icomm-address" || args[i] == "-ica" {
            i++;
            engineUri = args[i]
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
    http.HandleFunc("/radio/api/station/delete", deleteHandler)
    http.HandleFunc("/radio/api/station/put", putHandler)
    http.HandleFunc("/radio/api/audio/set", setHandler)
    http.HandleFunc("/radio/api/audio/get/station", getCurrentHandler)
    http.HandleFunc("/radio/api/audio/play", playHandler)
    http.HandleFunc("/radio/api/audio/stop", stopHandler)
    http.HandleFunc("/radio/api/audio/next", nextHandler)
    http.HandleFunc("/radio/api/audio/prev", prevHandler)
    http.HandleFunc("/radio/api/audio/state", stateHandler)
    http.HandleFunc("/radio", viewHandler)

    Log.Warn("serve uri: " + serveUri)
    errServe := http.ListenAndServe(serveUri, nil)
    if errServe != nil {
        Log.Err("error serve: " + errServe.Error()) 
    }
}
