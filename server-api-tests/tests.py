import requests as req
import json

URL = "http://localhost:8080/radio/api/"

def test():
    test_all(1)
    test_set(2)
    test_put(3)
    test_remove(4)


def test_all(test_num : int):
    responseMessage = req.get(URL + "station/all")
    expectedMessage = '''
    {
        "type":"REP",
        "message":"Stations database",
        "value": [
            {
                "name":"Anty-Radio",
                "uri":"http://redir.atmcdn.pl/sc/o2/Eurozet/live/antyradio.livx?audio=5"
            },
            {
                "name":"ESKA-ROCK",
                "uri":"http://waw02-03.ic.smcdn.pl:8000/t041-1.mp3"
            }
        ]
    }
    '''
    responseMessageJson = responseMessage.json()
    expectedMessageJson = json.loads(expectedMessage)
    
    assert responseMessageJson == expectedMessageJson, "Get all command failed!"
    print(str(test_num) + ". station get all ok!")


def test_set(test_num : int):
    requestMessageJson = {'name' : 'Anty-Radio'}
    expectedMessage = '''
    {
        "type": "INFO",
        "message": "Station setted and playing: Anty-Radio",
        "value": null
    }
    '''
    expectedMessageJson = json.loads(expectedMessage)
    responseMessage = req.get(URL + "station/set", data=json.dumps(requestMessageJson))
    responseMessageJson = responseMessage.json()

    assert expectedMessageJson == responseMessageJson, "Station do not setted and played!"
    print(str(test_num) + ". station set ok!")


def test_put(test_num : int):
    requestMessage = '''
    {
        "name" : "Pro-Radio",
        "uri" : "http://www.proradio.com"
    }   
    '''
    expectedMessage = '''
    {
        "type": "INFO",
        "message": "Station added to database: Pro-Radio http://www.proradio.com",
        "value": null
    }
    '''
    requestMessageJson = json.loads(requestMessage)
    expectedMessageJson = json.loads(expectedMessage)
    responseMessage = req.post(URL + "station/put", data=json.dumps(requestMessageJson))
    responseMessageJson = responseMessage.json()

    assert expectedMessageJson == responseMessageJson, "Station put failed!"
    print(str(test_num) + ". station put ok!")


def test_remove(test_num : int):
    requestMessageJson = {"name" : "Pro-Radio"}   
    expectedMessage = '''
    {
        "type": "INFO", 
        "message": "Station removed: Pro-Radio", 
        "value": null
    }
    '''
    expectedMessageJson = json.loads(expectedMessage)
    responseMessage = req.post(URL + "station/remove", data=json.dumps(requestMessageJson))
    responseMessageJson = responseMessage.json()
    assert expectedMessageJson == responseMessageJson, "Station remove failed!"
    print(str(test_num) + ". station removed ok!")
