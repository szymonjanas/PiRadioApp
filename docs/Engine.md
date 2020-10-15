Communication
======
> Communication is via IPC ( _Inter-Process Communication_ ).

## How does it works
App which we want to communicate must be run from same path as engine, because communication is via file. File is automatically created by engine in current folder. 

Best option is to use ZMQ to communicate. 

## Details
---
### Path 
```
ipc://piradio.app
```
### Message Format - JSON - to engine
```json
{
    "route" : "example/route",
    "value" : null
}   
```
`value` can contain JSON format, depends on route.

### Message Format - JSON - from engine
```json
{
    "code" : 200,
    "message" : "example ok message",
    "value" : null
}
```
- `code` - status code
- `value` can contain JSON format, depends on request eg. Array of stations

### Station JSON format - to engine
```json
{
    "name" : "example name",
    "uri" : "http://example.station"
}
```

### Station JSON format - from engine
```json
{
    "name" : "example name",
    "uri" : "http://example.station",
    "isPlaying" : false,
    "title" : "If it is"
}
```

### Engine State
- `play` 
- `pause` 
- `stop`
```json
{
    "state" : "play"
}
```

## Routes and Requirements
---
#### Database routes
1. `database/get/all` - return array of Stations
2. `database/put` - put new or change exist Station, **require** Station in JSON value
3. `database/delete` - delete Station, **require** only Station `name` in JSON value
#### Audio Routes
4. `audio/switch/prev` - previous station
5. `audio/switch/next` - next station
6. `audio/set/state` - set state **require** Engine State in JSON value
7. `audio/set/station` - set station **require** Station in JSON value
8. `audio/get/state` - return Engine State in JSON value
9. `audio/get/current` - return current Station in JSON value
