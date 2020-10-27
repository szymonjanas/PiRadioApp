[Main](README.md)

# Server Module Documentation

# Run Server
## Argumnets

<span style="color:red">
<b>IMPORTANT</b>
Arguments avaliable only when Engine run in `--only` mode, and you want to run server manually! [More details](Engine.md)
</span>

| Argument | Description | Default | 
| --- | --- | --- | 
| `-col` | Colors in terminal | no colors |
| `-ica [addr]` | Internal communication Address | `tcp://127.0.0.1:7982` | 
| `-sha [addr]` | Server host address | `:8080` |
| `--debug` | Show debug message | no debug msgs |
| `--basic` | Only important message | all msgs (except debug) |
| `-res [path]` | Resource path | `server/resource` |

# Communication with Server
> Communication with server is via **HTTP request**.

> Default running address (index page): http://127.0.0.1:7982/radio
> `7892` is ascii `OR` (_Online Radio_)
## Routes and Requirements 
--- 
| Route | Request (JSON body) | Reply | Description |
| --- | --- | --- | --- |
| `/radio` | none | none | index |
| `/radio/api/station/all` | none | `status`, Stations JSON array | get all avaliable station |
| `/radio/api/station/delete` | Station `name` | `status` | delete Station by `name` |
| `/radio/api/station/put` | Station `name` and `uri` | `status` | put new/change uri |
| `/radio/api/audio/set` | Station `name` | `status` | set Station by `name` |
| `/radio/api/audio/play` | none | `status` | play Audio **if Station setted** |
| `/radio/api/audio/stop` | none | `status` | stop Audio |
| `/radio/api/audio/next` | none | `status` | set next Station |
| `/radio/api/audio/prev` | none | `status` | set previous Station |
| `/radio/api/audio/state` | none | `status`, Audio `state` | get audio `state`: `play`, `stop` or `pause` |

## Example messages and JSON Bodies
---
### Station name JSON Body
```json
{
    "name" : "somestation"
}
```
### Station JSON Body
```json
{
    "name" : "somestation",
    "uri" : "http://example.uri"
}
```
### Status JSON Body
```json
{
    "code" : 200,
    "message" : "Command executed!",
    "value" : null
}
```

### Stations Array JSON Body
```json
{
    "code" : 200,
    "message" : "All Stations!",
    "value: [
        {
            "isPlaying" : true,
            "name" : "First Station",
            "uri" : "http://first.station",
            "title" : "audio track title"
        }, 
        {
            "isPlaying" : false,
            "name" : "Second Station",
            "uri" : "http://second.station",
            "title" : ""
        }, 
    ]
}
```

### Audio State
```json
{
    "state" : "play"
}
```



