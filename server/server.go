package main

import (
    "net/http"
    "os"
    "encoding/json"
    "io/ioutil"
    "html/template"
    zmq "github.com/pebbe/zmq4"
)

type SettingsStruct struct {
    Internal_Communication_Address string
    Server_Host_Address string
    Resource_Path string 
}
var Settings SettingsStruct

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
    Log.Debug("Send request: " + request)
    msg, err := (*client).RecvMessage(0)
    if err != nil {
        Log.Err("Sending error: " + err.Error())
    }
    reply := msg[0]
    Log.Debug("Secive replay: " + reply)
    return reply 
}

/* 
    HANDLERS: api 
*/

func viewHandler(w http.ResponseWriter, r *http.Request){
    tmpl, err := template.ParseFiles("../server/resources/index.html")
    if err != nil {
        Log.Err("Error occur: " + err.Error())
        w.WriteHeader(http.StatusInternalServerError)
        return
    }
    type Fake struct {}
    var obj Fake
    tmpl.Execute(w, obj)
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

    Settings.Internal_Communication_Address = "tcp://127.0.0.1:7982"
    Settings.Server_Host_Address = ":8080"
    Settings.Resource_Path = "server/resources"

    for i := 0; i < len(args); i++ {
        if args[i] == "-col" {
            ColorStatus = true
        } else if args[i] == "--basic" {
            Basic = true
        } else if args[i] == "-ica" {
            i++;
            Settings.Internal_Communication_Address = args[i]
        }  else if args[i] == "-sha" {
            i++;
            Settings.Server_Host_Address = args[i]
        }  else if args[i] == "-res" {
            i++;
            Settings.Resource_Path = args[i]
        } else if args[i] == "--debug" {
            DebugStatus = true
        }
    }

    Log.Warn("Internal Communication address: " + Settings.Internal_Communication_Address)
    Log.Warn("Server Host Address: " + Settings.Server_Host_Address)
    Log.Warn("Setted resource path: " + Settings.Resource_Path)
    if DebugStatus {
        Log.Warn("Debug mode on!")
    }
    if Basic {
        Log.Warn("Basic mode on!")
    }
    if ColorStatus {
        Log.Warn("Colors mode on!")
    }

    socket, errSocket := zmq.NewSocket(zmq.PAIR)
    client = socket

    (*client).Connect(Settings.Internal_Communication_Address)
    if errSocket != nil {
        Log.Err("Error socket: " + errSocket.Error())
    } else {
        Log.Warn("Internal connected to engine: " + Settings.Internal_Communication_Address)
    }
    
    http.Handle("/radio/res/", http.StripPrefix("/radio/res/", http.FileServer(http.Dir(Settings.Resource_Path))))
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

    Log.Info("Host running...")
    errServe := http.ListenAndServe(Settings.Server_Host_Address, nil)
    if errServe != nil {
        Log.Err("Error host: " + errServe.Error()) 
    }
}
