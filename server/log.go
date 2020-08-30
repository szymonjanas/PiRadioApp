package main

/*
	Print logs and save to file
*/

import (
	"fmt"
	"time"
	"os"
)

var ID string = "server: "
var coloredID string =  "\033" + "[1;32m" + ID + "\033" + "[0m"
var ColorStatus bool = false
var Basic bool = false
var LogFilePath string = "client.txt"

func getTime() string {
    t := time.Now()
    return t.Format("2006-01-02 15:04:05")
}

var c_red string = "[0;31m"
var c_blue string = "[0;34m"
var c_yellow string = "[1;33m"
var c_cyan string = "[1;36m"

var esc string = "\033"
var reset string = "[0m"

type record struct {
	color_ string
	type_ string
	message_ string
	time_ string
}

func (l *record) create_log_color() string {
	if l.type_ == "INFO" {
		return coloredID  + l.time_ + esc + l.color_ + " " + l.type_ + ": " + esc + reset + l.message_
	} else {
		return coloredID  + l.time_ + esc + l.color_ + " " + l.type_ + ": " + l.message_ + esc + reset 
	}
}

func (l *record) create_log_clear() string {
	return ID + l.time_ + " " + l.type_ + ": " + l.message_
}

type log string
var Log log = "log"

func (l *log) Debug(message string){
	if Basic {
		return
	} 
	msg := record{
		color_: c_cyan,
		type_: "DEBUG",
		message_: message,
		time_: getTime(),
	}
	msg.print_log()
}
func (l *log) Err(message string){
	msg := record{
		color_: c_red,
		type_: "ERROR",
		message_: message,
		time_: getTime(),
	}
	msg.print_log()
}
func (l *log) Warn(message string){
	msg := record{
		color_: c_yellow,
		type_: "WARN",
		message_: message,
		time_: getTime(),
	}
	msg.print_log() 
}
func (l *log) Info(message string){
	if Basic {
		return
	} 
	msg := record{
		color_: c_blue,
		type_: "INFO",
		message_: message,
		time_: getTime(),
	}
	msg.print_log() 
}


func (l *record) save_log(){
	f, err := os.OpenFile(LogFilePath, os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0644) 
	if err != nil {
		Log.Err(err.Error())
	}
    f.WriteString(l.create_log_clear() + "\n") 
    f.Close()
}

func (l *record) print_log(){
	if ColorStatus {
		fmt.Println(l.create_log_color())
	} else {
		fmt.Println(l.create_log_clear())
	}
	l.save_log()
}
