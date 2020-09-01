package main

/*
    TCP connection with engine
*/

import "strings"

type comm string
var Comm comm = "comm"

func (c *comm) SendRequest(request string) []string {
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
        Log.Info("MSG: " + informMessage.Message)
    }
    return words 
}