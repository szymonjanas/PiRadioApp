from testing import *
import requests as req
import json

URL = "http://localhost:8080/radio/api/"

def Database_get_all(expectedMessageJson : str = None):
    global URL
    if expectedMessageJson == None:
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
    return expectedMessageJson == responseMessageJson

def Database_put(requestMessageJson, expectedMessageJson):
    global URL
    responseMessage = req.post(URL + "station/put", data=json.dumps(requestMessageJson))
    responseMessageJson = responseMessage.json()
    return expectedMessageJson == responseMessageJson

def Database_delete(requestMessageJson, expectedMessageJson):
    global URL
    responseMessage = req.post(URL + "station/delete", data=json.dumps(requestMessageJson))
    responseMessageJson = responseMessage.json()
    return expectedMessageJson == responseMessageJson

@TestClass
class TestDatabase:
    def getAllFromTestDatabase(self):
        global URL
        TestCheck(Database_get_all(), "Get all command failed!")

    # INFO: put new station to database, check if station is listed in all stations,
    #       then delete that new station, and check if station was removed also from all stations 
    def putNewStationToDatabaseAndDeleteIt(self):
        global URL
        TestCheck(Database_get_all(), "Get all station command failed!")
        requestPutMessage = '''
        {
            "name": "newstation",
            "uri" : "http://newstation.app"
        }
        '''
        requestPutMessageJson = json.loads(requestPutMessage)
        expectedPutMessage = '''
        {
            "code": 200,
            "message": "Station added to database: newstation",
            "value": ""
        }
        '''
        expectedPutMessageJson = json.loads(expectedPutMessage)
        TestCheck(Database_put(requestPutMessageJson, expectedPutMessageJson), "Station put failed!")
        
        getAllWithNewStation = '''
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
        getAllWithNewStationJson = json.loads(getAllWithNewStation)
        TestCheck(Database_get_all(getAllWithNewStationJson), "New stations is not listed in station all, or somethink went wrong!")

        requestDeleteMessage = '''
        {
            "name": "newstation"
        }
        '''  
        requestDeleteMessageJson = json.loads(requestDeleteMessage)
        expectedMessage = '''
        {
            "code": 200,
            "message": "Station deleted: newstation",
            "value": ""
        }
        '''
        expectedMessageJson = json.loads(expectedMessage)
        TestCheck(Database_delete(requestDeleteMessageJson, expectedMessageJson), "Station delete failed!")

        TestCheck(Database_get_all(), "Station was not deleted or something went wrong!")

@TestClass
class TestAudio:

    # INFO: test chain
    # set -> play -> get current -> next -> prev -> stop
    def setAndPlayAndGetCurrnetAndNextAndPrevAndStop(self):
        global URL
        requestMessage = '''
        {
            "name": "Test Radio Two"
        }
        '''  
        requestMessageJson = json.loads(requestMessage)
        expectedMessage = '''
        {
            "code": 200,
            "message": "Station setted: Test Radio Two",
            "value": ""
        }
        '''
        expectedMessageJson = json.loads(expectedMessage)
        responseMessage = req.post(URL + "audio/set", data=json.dumps(requestMessageJson))
        responseMessageJson = responseMessage.json()
        TestCheck(expectedMessageJson == responseMessageJson, "Set station failed!")


        # play
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
        TestCheck(expectedMessageJson == responseMessageJson, "Engine state set play failed!")


        # get current
        expectedMessage = '''
        {
            "code": 200,
            "message": "Current station",
            "value": {
                "name": "Test Radio Two",
                "uri": "http://testradio.two/player?mp3",
                "isPlaying": true,
                "title": ""
            }
        }
        '''
        expectedMessageJson = json.loads(expectedMessage)
        responseMessage = req.get(URL + "audio/get/station")
        responseMessageJson = responseMessage.json()
        TestCheck(expectedMessageJson == responseMessageJson, "Get current station failed!")


        # next
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
        TestCheck(expectedMessageJson == responseMessageJson, "Station switch next failed!")

        # prev
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
        TestCheck(expectedMessageJson == responseMessageJson, "Station switch prev failed!")


        # stop
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
        TestCheck(expectedMessageJson == responseMessageJson, "Engine state set stop failed!")
