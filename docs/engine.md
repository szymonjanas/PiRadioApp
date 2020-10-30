[Main](README.md)

# Engine Module Documentation

# Run Engine
## Arguments
Example
```http
    ./PiRadioApp -col -db test-database.json
```

Some arguments send to engine are also pass to server (if not `--only` mode).

| Argument | Short | Description | Default | Example |
| --- | --- | --- | --- | --- | 
| `--help` | `-h` | only show help sheet | x | x |
| `--internal-communication-address [addr]` | `-ica [addr]` | set address | `tcp://127.0.0.1:7982` | `-ica tcp://127.0.0.1:5000` |
| `--server-host-address [addr]` | `-sha [addr]` | set host website/api | `:8080` | `-sha 127.0.0.1:8000` |
| `--debug` | x | debug mode (shows debug message) | no debug | x |
| `--only` | x | run only engine (without server) | run server | x | 
| `--database [path]` | `-db [path]` | set database file path | `~/radio-database.json` | `-db test-database.json` |
| `--colors` | `-col` | set colors in console [more](https://en.wikipedia.org/wiki/ANSI_escape_code#Colors) | no colors | x |
| `--basic` | x | only important messages (warn, err) | all std msgs | x |
| `--no-audio` | `-na` | no audio mode, mainly testing purpose | audio on | x | 
| `--run-server-cmd [cmd]` | `-rsc [cmd]` | set run server cmd | `./build/server` | `-rsc ./server` |
| `--resource [path]` | `-res [path]` | set server resource path ((!) without args) | `server/resources/` | `-res var/www` | 

# Communication with Engine

> Communication with engine is via **TCP** socket.

### **TCP Communication**
Communication via tcp socket require specific ip and port. Allows to control engine in local network.

Best option is to use framework ZMQ to communicate. 

## Routes and Requirements
---
| Route | [Request (value)](#message-format---json---to-engine) | [Reply](#message-format---json---from-engine) | Description |
| --- | --- | --- | --- |
| `database/get/all` | `route` | `status`, array of Stations | get all available Stations |
| `database/put` | `route`, [Station JSON](#station-json-format---to-engine) | `status` | put new/change exist: Station uri by `name` |
| `database/delete` | `route`, Station `name` in JSON | `status` | delete Station by `name` | 
| `audio/switch/prev` | `route` | `status` | previous station |
| `audio/switch/next` | `route` | `status` | next station |
| `audio/set/state` | `route`, `state` in JSON value | `status` | set [state](#engine-state): `play`, `pause` or `stop` |
| `audio/set/station` | `route` | `status`,Station `name` in JSON | set station by `name`| 
| `audio/get/state` | `route` | `status`,  `state` in JSON value | return Audio Engine [state](#engine-state) | 
| `audio/get/current` | `route` | `status`, return current Station in JSON value | return all detail about current station |
| `audio/volume/get` | `route` | `status` with `volume` | return volume level |
| `audio/volume/set` | `route`, `volume` | `status` with `volume` | set volume specific level, return volume level |
| `audio/volume/mute` | `route` | `status` with `volume` | set volume to off, or set previous level |
| `audio/volume/up` | `route` with `volume` | `status` with `volume` | increase volume with given `value` |
| `audio/volume/down` | `route` with `volue` | `status` with `volume` | decrease volume with given `value` |

`status` mean `code` and `message` about status of execution. [More Details](#message-format---json---from-engine)
More info about `volume` [here](server.md)

## Details
---
### Default Path 
```python
tcp://127.0.0.1:5010
```

### Message Format - JSON - to engine
<span style="color:red">
<b>IMPORTANT</b>
Messages must have JSON format, but they are sent and recive as string.
</span>

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

