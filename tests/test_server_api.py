import testing
import requests as req
import json

URL = "http://localhost:8080/radio/api/"

test = testing.TestClass()

#! ################
#! DATABASE GET ALL
#! ################

def test_database_get_all(expectedMessage : str = None ):
    global URL
    if expectedMessage == None:
        expectedMessage = '''
        {
            "code": 200,
            "message": "Stations",
            "value": [
                {
                    "name": "Test Radio One",
                    "uri": "http://testradio.one/stream",
                    "isPlaying": false,
                    "title": ""
                },
                {
                    "name": "Test Radio Two",
                    "uri": "http://testradio.two/player?mp3",
                    "isPlaying": false,
                    "title": ""
                }
            ]
        }
        '''
    expectedMessageJson = json.loads(expectedMessage)

    responseMessage = req.get(URL + "station/all")
    responseMessageJson = responseMessage.json()

    test.check(test_database_get_all.__name__, responseMessageJson == expectedMessageJson, "Get all command failed!")
test.add(test_database_get_all)


#! ############
#! DATABASE PUT
#! ############

def test_database_put():
    global URL
    requestMessage = '''
    {
        "name": "newstation",
        "uri" : "http://newstation.app"
    }
    '''
    requestMessageJson = json.loads(requestMessage)
    expectedMessage = '''
    {
        "code": 200,
        "message": "Station added to database: newstation",
        "value": ""
    }
    '''
    expectedMessageJson = json.loads(expectedMessage)

    responseMessage = req.post(URL + "station/put", data=json.dumps(requestMessageJson))
    responseMessageJson = responseMessage.json()

    test.check(test_database_put.__name__, expectedMessageJson == responseMessageJson, "Station put failed!")
    
    getAllMsg = '''
    {
        "code": 200,
        "message": "Stations",
        "value": [
            {
                "name": "Test Radio One",
                "uri": "http://testradio.one/stream",
                "isPlaying": false,
                "title": ""
            },
            {
                "name": "Test Radio Two",
                "uri": "http://testradio.two/player?mp3",
                "isPlaying": false,
                "title": ""
            },
            {
                "name": "newstation",
                "uri": "http://newstation.app",
                "isPlaying": false,
                "title": ""
            }
        ]
    }
    '''
    test_database_get_all(getAllMsg)
test.add(test_database_put)


#! #################
#! AUDIO STATION SET
#! #################

def test_audio_set():
    global URL
    requestMessage = '''
    {
        "name": "newstation"
    }
    '''  
    requestMessageJson = json.loads(requestMessage)
    expectedMessage = '''
    {
        "code": 200,
        "message": "Station setted: newstation",
        "value": ""
    }
    '''
    expectedMessageJson = json.loads(expectedMessage)
    responseMessage = req.post(URL + "audio/set", data=json.dumps(requestMessageJson))
    responseMessageJson = responseMessage.json()
    test.check(test_audio_set.__name__, expectedMessageJson == responseMessageJson, "Set station failed!")
test.add(test_audio_set)


#! #################
#! AUDIO GET CURRENT
#! #################

def test_audio_get_current():
    global URL
    expectedMessage = '''
    {
        "code": 200,
        "message": "Current station",
        "value": {
            "name": "newstation",
            "uri": "http://newstation.app",
            "isPlaying": false,
            "title": ""
        }
    }
    '''
    expectedMessageJson = json.loads(expectedMessage)
    responseMessage = req.get(URL + "audio/get/station")
    responseMessageJson = responseMessage.json()
    test.check(test_audio_get_current.__name__, expectedMessageJson == responseMessageJson, "Get current station failed!")
test.add(test_audio_get_current)


#! ##########
#! AUDIO PLAY
#! ##########

def test_audio_play():
    global URL
    expectedMessage = '''
    {
        "code": 200,
        "message": "Audio state is: play",
        "value": ""
    }
    '''
    expectedMessageJson = json.loads(expectedMessage)

    responseMessage = req.get(URL + "audio/play")
    responseMessageJson = responseMessage.json()
    test.check(test_audio_play.__name__, expectedMessageJson == responseMessageJson, "Engine state set play failed!")

    getAllMsg = '''
    {
        "code": 200,
        "message": "Stations",
        "value": [
            {
                "name": "Test Radio One",
                "uri": "http://testradio.one/stream",
                "isPlaying": false,
                "title": ""
            },
            {
                "name": "Test Radio Two",
                "uri": "http://testradio.two/player?mp3",
                "isPlaying": false,
                "title": ""
            },
            {
                "name": "newstation",
                "uri": "http://newstation.app",
                "isPlaying": true,
                "title": ""
            }
        ]
    }
    '''
    test_database_get_all(getAllMsg)
test.add(test_audio_play)


#! ##########
#! AUDIO STOP
#! ##########

def test_audio_stop():
    global URL
    expectedMessage = '''
    {
        "code": 200,
        "message": "Audio state is: stop",
        "value": ""
    }
    '''
    expectedMessageJson = json.loads(expectedMessage)
    responseMessage = req.get(URL + "audio/stop")
    responseMessageJson = responseMessage.json()
    test.check(test_audio_stop.__name__, expectedMessageJson == responseMessageJson, "Engine state set stop failed!")

    getAllMsg = '''
    {
        "code": 200,
        "message": "Stations",
        "value": [
            {
                "name": "Test Radio One",
                "uri": "http://testradio.one/stream",
                "isPlaying": false,
                "title": ""
            },
            {
                "name": "Test Radio Two",
                "uri": "http://testradio.two/player?mp3",
                "isPlaying": false,
                "title": ""
            },
            {
                "name": "newstation",
                "uri": "http://newstation.app",
                "isPlaying": false,
                "title": ""
            }
        ]
    }
    '''
    test_database_get_all(getAllMsg)
test.add(test_audio_stop)


#! ##########
#! AUDIO NEXT
#! ##########

def test_audio_next():
    global URL
    expectedMessage = '''
    {
        "code": 200,
        "message": "Station switch: next",
        "value": ""
    }
    '''
    expectedMessageJson = json.loads(expectedMessage)

    responseMessage = req.get(URL + "audio/next")
    responseMessageJson = responseMessage.json()
    test.check(test_audio_next.__name__, expectedMessageJson == responseMessageJson, "Station switch next failed!")
test.add(test_audio_next)


#! ##########
#! AUDIO PREV
#! ##########

def test_audio_prev():
    global URL
    expectedMessage = '''
    {
        "code": 200,
        "message": "Station switch: previous",
        "value": ""
    }
    '''
    expectedMessageJson = json.loads(expectedMessage)

    responseMessage = req.get(URL + "audio/prev")
    responseMessageJson = responseMessage.json()
    test.check(test_audio_prev.__name__, expectedMessageJson == responseMessageJson, "Station switch prev failed!")
test.add(test_audio_prev)


#! ###############
#! DATABASE DELETE
#! ###############

def test_database_delete():
    global URL
    requestMessage = '''
    {
        "name": "newstation"
    }
    '''  
    requestMessageJson = json.loads(requestMessage)
    expectedMessage = '''
    {
        "code": 200,
        "message": "Station deleted: newstation",
        "value": ""
    }
    '''
    expectedMessageJson = json.loads(expectedMessage)

    responseMessage = req.post(URL + "station/delete", data=json.dumps(requestMessageJson))
    responseMessageJson = responseMessage.json()
    test.check(test_database_delete.__name__, expectedMessageJson == responseMessageJson, "Station delete failed!")
    test_database_get_all()
test.add(test_database_delete)
