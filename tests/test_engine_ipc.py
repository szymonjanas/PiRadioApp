import testing
import zmq
import json


context = zmq.Context()
socket = context.socket(zmq.PAIR)

test = testing.TestClass()
debugFlag = test.debugFlag

def disconnect(address : str):
    global socket
    socket.disconnect(address)
    print("DISCONNECTED: " + address)

def connect(address : str):
    global socket
    socket.connect(address)    
    print("CONNECTED: " + address)

ipcFlag = False
def send(message : str):
    global ipcFlag
    if ipcFlag:
        print("Send message: " + message)
    socket.send_string(message)
    reply = (socket.recv()).decode()
    if ipcFlag:
        print("Recv message: " + reply)
    return reply


# ANCHOR TEST CASES ##################################################

#! ################
#! DATABASE GET ALL
#! ################
def test_database_get_all(expectedResponse : str = None):
    global debugFlag
    request = '''
    {
        "route" : "database/get/all",
        "value" : ""
    }
    '''
    requestJson = json.loads(request)
    response = send(json.dumps(requestJson))
    responseJson = json.loads(response)
    if expectedResponse == None:
        expectedResponse = '''
        {
            "code": 200,
            "message":"Stations",
            "value":[
                {
                    "isPlaying": false,
                    "name":"Test Radio One",
                    "title":"",
                    "uri":"http://testradio.one/stream"
                },
                {
                    "isPlaying": false,
                    "name":"Test Radio Two",
                    "title":"",
                    "uri":"http://testradio.two/player?mp3"
                }
            ]
        }
        '''
    expectedResponseJson = json.loads(expectedResponse)
    if debugFlag:
        print("DEBUG: ")
        print("EXP: " + json.dumps(expectedResponseJson))
        print("GOT: " + json.dumps(responseJson))
    test.check(test_database_get_all.__name__, responseJson == expectedResponseJson, "Response is diffrent. Probably database not found!")
test.add(test_database_get_all)


#! ############
#! DATABASE PUT
#! ############
def test_database_put_new(putStation = None):
    global debugFlag
    request = '''
    {
        "route" : "database/put",
        "value" : {
            "name" : "newstation",
            "uri" : "http://newstation.play"
        }
    }
    '''
    expectedResponseAll = '''
        {
            "code": 200,
            "message":"Stations",
            "value":[
                {
                    "isPlaying":false,
                    "name":"Test Radio One",
                    "title":"",
                    "uri":"http://testradio.one/stream"
                },
                {
                    "isPlaying":false,
                    "name":"Test Radio Two",
                    "title":"",
                    "uri":"http://testradio.two/player?mp3"
                }, 
                {
                    "isPlaying":false,
                    "name":"newstation",
                    "title":"",
                    "uri":"http://newstation.play"
                }
            ]
        }
    '''
    requestJson = json.loads(request)
    if putStation != None:
        requestJson["value"]["name"] = putStation[0]
        requestJson["value"]["uri"]  = putStation[1]
    print("SENT: ", json.dumps(requestJson))
    response = send(json.dumps(requestJson))
    responseJson = json.loads(response)
    expectedResponse = '''
    {
        "code": 200, 
        "message": "Station added to database: newstation", 
        "value": null
    }
    '''
    expectedResponseJson = json.loads(expectedResponse)
    if putStation != None:
        expectedResponseJson["message"] = "Station added to database: " + putStation[0]
    if debugFlag:
        print("DEBUG: ")
        print("EXP: " + json.dumps(expectedResponseJson))
        print("GOT: " + json.dumps(responseJson))
    test.check(test_database_put_new.__name__, expectedResponseJson == responseJson, "Station put to database error!")
    if putStation != None:
        expectedResponseAllJson = json.loads(expectedResponseAll)
        expectedResponseAllJson["value"][2]["name"] = putStation[0]
        expectedResponseAllJson["value"][2]["uri"]  = putStation[1]
        expectedResponseAll = json.dumps(expectedResponseAllJson)
    test_database_get_all(expectedResponseAll)
test.add(test_database_put_new)

#! ###############
#! DATABASE DELETE
#! ###############
def test_database_delete(deleteStationName = None):
    global debugFlag
    request = '''
    {
        "route" : "database/delete",
        "value" : 
        {
            "name" : "newstation"
        }
    }
    '''
    expectedResponse = '''
    {
        "code" : 200,
        "message": "Station deleted: newstation", 
        "value": null
    }
    '''
    requestJson = json.loads(request)
    expectedResponseJson = json.loads(expectedResponse)
    if deleteStationName != None:
        requestJson["value"]["name"] = deleteStationName
        expectedResponseJson["message"] = "Station deleted: " + deleteStationName
    response = send(json.dumps(requestJson))
    responseJson = json.loads(response)
    if debugFlag:
        print("DEBUG")
        print("EXP: " + json.dumps(expectedResponseJson))
        print("GOT: " + json.dumps(responseJson))
    test.check( test_database_delete.__name__, expectedResponseJson == responseJson, "Error! Station could not be deleted!")
    test_database_get_all()
test.add(test_database_delete)


#! #################
#! AUDIO SET STATION
#! #################
def test_audio_set_station(setStationName = None):
    global debugFlag
    request = '''
    {
        "route" : "audio/set/station",
        "value" : {
            "name" : "newstation"
        }
    }
    '''
    expectedResponse = '''
    {
        "code" : 200,
        "message": "Station setted: newstation", 
        "value": null
    }
    '''
    requestJson = json.loads(request)
    expectedResponseJson = json.loads(expectedResponse)
    if setStationName == None:
        test_database_put_new()
    else:
        requestJson["value"]["name"] = setStationName
        expectedResponseJson["message"] = "Station setted: " + setStationName
    response = send(json.dumps(requestJson))
    responseJson = json.loads(response)
    if debugFlag:
        print("DEBUG")
        print("EXP: " + json.dumps(expectedResponseJson))
        print("GOT: " + json.dumps(responseJson))
    test.check( test_audio_set_station.__name__, expectedResponseJson == responseJson, "Error! Station could not be setted or played!")
    if setStationName == None:
        test_database_delete()
test.add(test_audio_set_station)


#! #################
#! AUDIO GET CURRENT
#! #################
def test_audio_get_current(compareJson = None):
    global debugFlag
    request = '''
    {
        "route" : "audio/get/current",
        "value" : ""
    }
    '''
    requestJson = json.loads(request)
    expectedResponse = '''
    {
        "code": 200, 
        "message": "Current station", 
        "value": 
        {
            "isPlaying": false, 
            "name": "newstation", 
            "title": "", 
            "uri": "http://newstation.play"
        }
    }
    '''
    expectedResponseJson = json.loads(expectedResponse)
    
    if compareJson == None:
        test_database_put_new()
        test_audio_set_station("newstation")
    response = send(json.dumps(requestJson))
    responseJson = json.loads(response)
    if debugFlag:
        print("DEBUG")
        if compareJson == None:
            print("EXP: " + json.dumps(expectedResponseJson))
        else:
            print("EXPC: " + json.dumps(compareJson))
        print("GOT: " + json.dumps(responseJson))
    if compareJson == None:
        test.check( test_audio_get_current.__name__, expectedResponseJson == responseJson, "Error! Station could not be setted or played!")
        test_database_delete("newstation")
    else:
        test.check( test_audio_get_current.__name__, compareJson == responseJson, "Error! Station could not be setted or played!")
test.add(test_audio_get_current)


#! #################
#! AUDIO SWITCH PREV
#! #################
def test_audio_switch_prev():
    global debugFlag
    request = '''
    {
        "route" : "audio/switch/prev",
        "value" : ""
    }
    '''
    requestJson = json.loads(request)
    expectedResponse = '''
    {
        "code": 200, 
        "message": "Station switch: previous", 
        "value": null
    }
    '''
    expectedResponseJson = json.loads(expectedResponse)
    
    test_database_put_new()
    test_audio_set_station("newstation")

    response = send(json.dumps(requestJson))
    responseJson = json.loads(response)
    
    if debugFlag:
        print("DEBUG")
        print("EXP: " + json.dumps(expectedResponseJson))
        print("GOT: " + json.dumps(responseJson))
    
    test.check( test_audio_switch_prev.__name__, expectedResponseJson == responseJson, "Error! Station could not be setted or played!")
    
    expectedCurrentResponse = '''
    {
        "code": 200, 
        "message": "Current station", 
        "value": 
        {
            "isPlaying":false,
            "name":"Test Radio Two",
            "title":"",
            "uri":"http://testradio.two/player?mp3"
        }
    }
    '''
    expectedCurrentResponseJson = json.loads(expectedCurrentResponse)
    test_audio_get_current(expectedCurrentResponseJson)
    test_database_delete("newstation")
test.add(test_audio_switch_prev)


#! #################
#! AUDIO SWITCH NEXT
#! #################
def test_audio_switch_next():
    global debugFlag
    request = '''
    {
        "route" : "audio/switch/next",
        "value" : ""
    }
    '''
    requestJson = json.loads(request)
    expectedResponse = '''
    {
        "code": 200, 
        "message": "Station switch: next", 
        "value": null
    }
    '''
    expectedResponseJson = json.loads(expectedResponse)
    
    test_database_put_new()
    test_audio_set_station("newstation")

    response = send(json.dumps(requestJson))
    responseJson = json.loads(response)
    
    if debugFlag:
        print("DEBUG")
        print("EXP: " + json.dumps(expectedResponseJson))
        print("GOT: " + json.dumps(responseJson))
    
    test.check( test_audio_switch_next.__name__, expectedResponseJson == responseJson, "Error! Station could not be setted or played!")
    
    expectedCurrentResponse = '''
    {
        "code": 200, 
        "message": "Current station", 
        "value": 
        {
            "isPlaying": false,
            "name":"Test Radio One",
            "title":"",
            "uri":"http://testradio.one/stream"
        }
    }
    '''
    test_audio_get_current(json.loads(expectedCurrentResponse))
    test_database_delete("newstation")
test.add(test_audio_switch_next)
