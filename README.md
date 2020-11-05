
# <img src="server/resources/favicon.png" width="32">  PiRadio
[![Build Status](https://travis-ci.com/PiRadioApp/PiRadioApp.svg?branch=master)](https://travis-ci.com/PiRadioApp/PiRadioApp)
## Description
```
Simple embedded radio player.
Control device radio via local website and play online radio from given stream URL on Linux (e.g. Raspberry Pi).
```
```
version v.1.0
```

## Features:
- playing radio from any audio stream,
- remote control and manage through web: local website, http rest api, 
- database in json file -> easy to manage,

## Whats more:
- colorfull console logs from engine and server,
- logs saved to file,

### Simple user manual:
1. install app on linux (especially usefull with raspberry pi (ver 3B/4)),
2. add station - url address to radio stream,
3. plug raspberry to audio device (speakers),
4. go on website `http://localhost:8081/radio` (default), play and enjoy your favourite online radio, and control it through the website.

## Download & Install
---
To make sure that every format is working install **gstreamer plugins**:
```
sudo apt-get install gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly
```
### piradio.deb

1. Download
   <!-- TODO -->

2. Install
    ```
        sudo dpkg -i PiRadioApp-v1.0.deb
    ```

### piradio.tar
1. Download
   <!-- TODO -->

2. Unpack tar. 
   ```Cpp
        tar xvf piradio.tar.gz
   ```
3. Install:
   ```Cpp
        sh INSTALL.sh
   ```
   Password for sudo is needed!
4. If everything went good, you can remove downloaded files.
   ```Cpp
        rm piradio.tar
        rm -r piradio 
   ```

## Run & Settings
---
**Application is running in background, and is avaliable (default) on website** `http://localhost:8082/radio`. 
- To run aplication in background type:
    ```Cpp
        sudo systemctl enable piradio.service
    ```
    To run application:
    ```Cpp
        sudo systemctl start piradio.service
    ```
    To check if application is running:
    ```Cpp
        sudo systemctl status piradio.service
    ```
    To reload daemon (could be required):
    ```Cpp
        sudo systemctl daemon-reload
    ```
- To change setting while running or because app not running.
    ```Cpp
        sudo systemctl stop piradio.service
    ```
    Settings (flags) you can change in `run.sh` script located in `/opt/PiRadioApp`.
    ```Cpp
        sudo systemctl start piradio.service
    ```
    Can be require to reload daemon.
    ```
        sudo systemctl daemon-reload
    ```


--- 

### [Developer manual](docs/developer_manual.md)

### Author:
@szymonjanas

### Licence:
<!-- TODO -->
