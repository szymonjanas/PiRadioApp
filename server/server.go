package main

import (
    "html/template"
    "net/http"
    "os"
    "fmt"
    "time"
    "strings"
    zmq "github.com/pebbe/zmq4"
)

var ID string = "server: "
var coloredID string =  "\033" + "[1;32m" + ID + "\033" + "[0m"
var colorStatus bool = true
var logFilePath string = "client.txt"
func log_time(message string) string {
    t := time.Now()
    str := t.Format("2006-01-02 15:04:05")
    return str + "  " + message
}
func log_file(message string){
    f, _ := os.OpenFile(logFilePath, os.O_APPEND|os.O_WRONLY, 0644) 
    f.WriteString(message) 
    f.Close()
}
func log_debug(message string){
    var str string
    message = log_time("DEBUG: " + message)
    log_file(ID + message + "\n")
    if colorStatus {
        str = coloredID + "\033" + "[1;36m" + message + "\033" + "[0m" + "\n"
    } else {
        str = ID + message + "\n"
    }
    fmt.Print(str)
}
func log_err(message string){
    var str string
    message = log_time("ERROR: "+ message)
    log_file(ID + message + "\n")
    if colorStatus {
        str = coloredID + "\033" + "[0;31m" + message + "\033" + "[0m" + "\n"
    } else {
        str = ID + message + "\n"
    }
    fmt.Print(str) 
}
func log_warn(message string){
    var str string
    message = log_time("WARN: " + message)
    log_file(ID + message + "\n")
    if colorStatus {
        str = coloredID + "\033" + "[1;33m" + message + "\033" + "[0m" + "\n"
    } else {
        str = ID + message + "\n"
    }
    fmt.Print(str)  
}
func log_info(message string){
    var str string
    message = log_time("INFO: " + message)
    log_file(ID + message + "\n")
    if colorStatus {
        str = coloredID + "\033" + "[0;34m" + message + "\033" + "[0m" + "\n"
    } else {
        str = ID + message + "\n"
    }
    fmt.Print(str)
}

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
}

func getStations() []StationsName {
    var stations []StationsName
    strStations := sendRequest("station get all")
    for i := range strStations {
        stations = append(stations, StationsName{strStations[i]})
    }
    return stations
}

/* 
    HANDLERS: api 
*/

func viewHandler(w http.ResponseWriter, r *http.Request){
    log_debug("main page")
    tmpl, err := template.ParseFiles("../server/resources/server.html")
    if err != nil {
        log_err("Error occure: " + err.Error())
        w.WriteHeader(http.StatusInternalServerError)
        return
    }
    
    current := sendRequest("station get current")
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
    }

    tmpl.Execute(w, details)
}

func playHandler(w http.ResponseWriter, r *http.Request){
    sendRequest("engine state set play")
    log_info("play ")
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func stopHandler(w http.ResponseWriter, r *http.Request){
    sendRequest("engine state set stop")
    log_info("stop")
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func setHandler(w http.ResponseWriter, r *http.Request){
    body := r.FormValue("Stations")
    checkedStation = body
    log_info("checked " + checkedStation)
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func submitHandler(w http.ResponseWriter, r *http.Request){
    sendRequest("station set " + checkedStation)
    sendRequest("engine state set play")
    log_info("submit " + checkedStation)
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func setsubmitHandler(w http.ResponseWriter, r *http.Request){
    body := r.FormValue("Stations")
    checkedStation = body
    sendRequest("station set " + checkedStation)
    sendRequest("engine state set play")
    log_info("checked and submit " + checkedStation)
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func removeHandler(w http.ResponseWriter, r *http.Request){
    sendRequest("station remove " + checkedStation)
    log_info("remove " + checkedStation)
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

func addHandler(w http.ResponseWriter, r *http.Request){
    name := r.FormValue("stationName")
    uri := r.FormValue("stationUri")
    sendRequest("station new " + name + " " + uri)
    log_info("add new " + name + " " + uri)
    http.Redirect(w, r, "/radio/", http.StatusFound)
} 

/*
    TCP connection with engine
*/

func sendRequest(request string) []string {
    /*
        send request; recive, decode and return reply
    */
    (*client).SendMessage(request, 0)
    log_info("send request: " + request)
    msg, err := (*client).RecvMessage(0)
    if err != nil {
        log_err("send error: " + err.Error())
    }
    reply := msg[0]
    log_info("recive replay: " + reply)
    var words []string
	word := ""
	flag := true
	iter := -1
	for i := range reply {
		if reply[i] == ' ' {
			flag = true
		} else if flag {
			word = ""
			words = append(words, word)
			iter++
			words[iter] = words[iter] + string(reply[i])
			flag = false
		} else {
			words[iter] = words[iter] + string(reply[i])
		}
    }
    if words[0] == "msg" || words[0] == "err" {
        if words[0] == "msg"{
            informMessage.Type = true
        } else {
            informMessage.Type = false
        }
        informMessage.Message = strings.Join(words[1:len(words)], " ")
        log_info("MSG: " + informMessage.Message)
    }
    return words 
}

func main() {
    socket, errSocket := zmq.NewSocket(zmq.PAIR)
    client = socket
    engineUri := "tcp://localhost:5555"
    serveUri := ":8080"
    (*client).Connect(engineUri)
    if errSocket != nil {
        log_err("error socket: " + errSocket.Error())
    } else {
        log_info("connected to server: " + engineUri)
    }
    
    http.Handle("/radio/res/", http.StripPrefix("/radio/res/", http.FileServer(http.Dir("../server/resources/"))))
    http.HandleFunc("/radio/api/play", playHandler)
    http.HandleFunc("/radio/api/stop", stopHandler)
    http.HandleFunc("/radio/api/set", setHandler)
    http.HandleFunc("/radio/api/submit", submitHandler)
    http.HandleFunc("/radio/api/setsubmit", setsubmitHandler)
    http.HandleFunc("/radio/api/remove", removeHandler)
    http.HandleFunc("/radio/api/add", addHandler)
    http.HandleFunc("/radio/", viewHandler)

    log_info("serve uri: " + serveUri)
    errServe := http.ListenAndServe(serveUri, nil)
    if errServe != nil {
        log_err("error serve: " + errServe.Error()) 
    }
}
