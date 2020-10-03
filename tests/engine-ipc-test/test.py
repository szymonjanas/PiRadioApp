import zmq
import json

context = zmq.Context()
socket = context.socket(zmq.PAIR)
socket.connect("ipc://piradio.app")

debugFlag = False
ipcFlag = False
testNumber = 1

testsList = []
def test():
    for func in testsList:
        func()

def send(message : str):
    global ipcFlag
    if ipcFlag:
        print("Send message: " + message)
    socket.send_string(message)
    reply = (socket.recv()).decode()
    if ipcFlag:
        print("Recv message: " + reply)
    return reply



#! ################
#! DATABASE GET ALL
#! ################
def test_database_get_all(expectedResponse : str = None):
    global debugFlag
    request = '''
    {
        "type" : "get",
        "applies" : "database",
        "command" : "all",
        "station" : null
    }
    '''
    requestJson = json.loads(request)
    response = send(json.dumps(requestJson))
    responseJson = json.loads(response)
    if expectedResponse == None:
        expectedResponse = '''
        {
            "message":"Stations database",
            "type":"REP",
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
                }
            ]
        }
        '''
    expectedResponseJson = json.loads(expectedResponse)
    if debugFlag:
        print("DEBUG: ")
        print("EXP: " + json.dumps(expectedResponseJson))
        print("GOT: " + json.dumps(responseJson))
    assert responseJson == expectedResponseJson, "Response is diffrent. Probably database not found!"
    global testNumber
    print(str(testNumber) +  ". Test OK! database get all")
    testNumber += 1
testsList.append(test_database_get_all)


#! ############
#! DATABASE PUT
#! ############
def test_database_put_new():
    global debugFlag
    request = '''
    {
        "type" : "put",
        "applies" : "database",
        "command" : "station",
        "station" : {
            "name" : "newstation",
            "uri" : "http://newstation.play"
        }
    }
    '''
    expectedResponseAll = '''
        {
            "message":"Stations database",
            "type":"REP",
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
    response = send(json.dumps(requestJson))
    responseJson = json.loads(response)
    expectedResponse = '''
    {
        "message": "Station added to database: newstation http://newstation.play", 
        "type": "INFO", 
        "value": null
    }
    '''
    expectedResponseJson = json.loads(expectedResponse)
    if debugFlag:
        print("DEBUG: ")
        print("EXP: " + json.dumps(expectedResponseJson))
        print("GOT: " + json.dumps(responseJson))
    assert expectedResponseJson == responseJson, "Station put to database error!"
    global testNumber
    print(str(testNumber) + ". Test OK! database put new")
    testNumber += 1
    test_database_get_all(expectedResponseAll)
testsList.append(test_database_put_new)

#! ###############
#! DATABASE DELETE
#! ###############
def test_database_delete():
    global debugFlag
    request = '''
    {
        "type" : "delete",
        "applies" : "database",
        "command" : "station",
        "station" : {
            "name" : "newstation"
        }
    }
    '''
    expectedResponse = '''
    {
        "message": "Station deleted: newstation", 
        "type": "INFO", 
        "value": null
    }
    '''
    requestJson = json.loads(request)
    response = send(json.dumps(requestJson))
    responseJson = json.loads(response)
    expectedResponseJson = json.loads(expectedResponse)
    if debugFlag:
        print("DEBUG")
        print("EXP: " + json.dumps(expectedResponseJson))
        print("GOT: " + json.dumps(responseJson))
    assert expectedResponseJson == responseJson, "Error! Station could not be deleted!"
    global testNumber
    print(str(testNumber) + ". Test OK! database delete station")
    testNumber += 1
    test_database_get_all()
testsList.append(test_database_delete)


#! #################
#! AUDIO SET STATION
#! #################
def test_audio_set_station():
    global debugFlag
    request = '''
    {
        "type" : "set",
        "applies" : "audio",
        "command" : "station",
        "station" : {
            "name" : "newstation"
        }
    }
    '''
    expectedResponse = '''
    {
        "message": "Station setted and playing: newstation", 
        "type": "INFO", 
        "value": null
    }
    '''
    requestJson = json.loads(request)
    test_database_put_new()
    response = send(json.dumps(requestJson))
    responseJson = json.loads(response)
    expectedResponseJson = json.loads(expectedResponse)
    if debugFlag:
        print("DEBUG")
        print("EXP: " + json.dumps(expectedResponseJson))
        print("GOT: " + json.dumps(responseJson))
    assert expectedResponseJson == responseJson, "Error! Station could not be setted or played!"
    global testNumber
    print(str(testNumber) + ". Test OK! station setted and audio played")
    testNumber += 1
testsList.append(test_audio_set_station)
