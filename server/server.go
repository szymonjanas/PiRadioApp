package main

import (
    "html/template"
    "net/http"
    "log"
    "fmt"
    zmq "github.com/pebbe/zmq4"
)

var client *zmq.Socket

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
}

func getStations() []StationsName {
    var stations []StationsName
    strStations := sendRequest("get station all")
    for i := range strStations {
        stations = append(stations, StationsName{strStations[i]})
    }
    return stations
}

func viewHandler (w http.ResponseWriter, r *http.Request){
    fmt.Println("view")
    tmpl, err := template.ParseFiles("../server/server.html")
    if err != nil {
        fmt.Println("Error occure", err)
        w.WriteHeader(http.StatusInternalServerError)
        return
    }
    details := ViewPageData {
        StationsData: StationsPageData{
            Stations: getStations(),
        },
        PlayingData: PlayingDetails {
            Station: sendRequest("get details name")[0],
            Title: sendRequest("get details title")[0],
            Url: sendRequest("get details uri")[0],
        },
    }

    tmpl.Execute(w, details)
}

func playHandler(w http.ResponseWriter, r *http.Request){
    sendRequest("set state play")
    http.Redirect(w, r, "/radio/", http.StatusFound)
    fmt.Println("PLAY")
} 

func stopHandler(w http.ResponseWriter, r *http.Request){
    sendRequest("set state stop")
    http.Redirect(w, r, "/radio/", http.StatusFound)
    fmt.Println("STOP")
} 


func setHandler(w http.ResponseWriter, r *http.Request){
    body := r.FormValue("Stations")
    http.Redirect(w, r, "/radio/", http.StatusFound)
    sendRequest("set station " + body)
    fmt.Println(body)
} 

func sendRequest(request string) []string {
    fmt.Println("Send request: " + request)
    (*client).SendMessage(request, 0)
    msg, err := (*client).RecvMessage(0)
    if err != nil {
        fmt.Println("ERROR")
        fmt.Println(err)
    }
    reply := msg[0]
    fmt.Println("Get replay: " + msg[0])
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
    return words 
}

func main() {
    socket, _ := zmq.NewSocket(zmq.PAIR)
    client = socket
    (*client).Connect("tcp://localhost:5555")
    fmt.Println("Connected to server")
    
    http.Handle("/css/", http.StripPrefix("/css/", http.FileServer(http.Dir("../server/"))))
    http.HandleFunc("/radio/play", playHandler)
    http.HandleFunc("/radio/stop", stopHandler)
    http.HandleFunc("/radio/set", setHandler)
    http.HandleFunc("/radio/", viewHandler)
    log.Fatal(http.ListenAndServe(":8080", nil))
}
