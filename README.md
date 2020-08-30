# PiRadio App

## Description
```
Simple embedded radio player.
Play online radio from given stream URL on Linux (e.g. Raspberry Pi).
```
## Features:
- playing radio from any radio stream,
- remote control through web: local website, http rest api, 
- managing radio stations (add/remove/change),
- storeging radio stations in simple database (txt file),

## Technology
### Engine:
- C/C++
- Gstreamer - audio engine,
- ZMQ - ipc communication,
- CMake,
### Server
- Golang - host website,
- ZMQ - ipc communication,
- html/css/js,

## How to use
### Simple user manual:
1. deploy app on linux (especially usefull with raspberry pi (ver 3B/4)),
2. add station - url address to radio stream,
3. plug raspberry to audio device (speakers),
4. play and enjoy your favourite online radio, and control it through the website.

More about deploy and use you can read in `wiki`.
### Install and Run