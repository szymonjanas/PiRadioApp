# Developer manual

## Requirements
Supported OS (tested):
- Raspbian 5.4 Lite (Raspberry 3B+)
- Ubuntu 18.04 or newer
- Linux Mint 20 Ulyana Cinnamon
- WSL Ubuntu 18.04 - NO AUDIO MODE
- WSL Ubuntu 20.04 - NO AUDIO MODE
# Setup
Download repository
```
git clone git@github.com:PiRadioApp/PiRadioApp.git
```
## Quick and fast setup
---
### Build
```Cpp
cd PiRadioApp/scripts
sudo sh install_enviroment.sh
sudo sh build.sh
```
### Example run
```Cpp
cd ../build
./PiRadioApp -res ../server/resource -db ../test-database.json
```

## Manual setup
---
[Instruction here](developer_manual_install.md)

### Enviroment (dependencies)
Follow steps in `scripts/install_enviroment.sh` to detect where the problem is. Remember that `apt` require `sudo` access to install.

Compilators require (tested): gcc-9 g++-9 (C++14 support)
Golang: 1.13

### Build
```Cpp
sh scripts/build.sh
```

### Link Front-End
use proper [flag](server.md) to set resources directory.
Directory required resource structure:
```Shell
- resources/
    - index.html
    - favicon.png
```
All you put in resources will be delivered by server ([more](server.md))

Example resource structure:
```Shell
- resources/
    - index.html
    - favicon.png
    - css/
        - example.css
    - js/
        - example.js
    - img/
        - example.jpg
    - supportfile.txt
```
Then:
- `example.css` will be avaliable at `/radio/res/css/example.css`
- `example.js` will be avaliable at `/radio/res/js/example.js`
- `example.jpg` will be avaliable at `/radio/res/js/example.jpg`
- `supportfile.txt` will be avaliable at `/radio/res/supportfile.txt`

With that you are able to build flexible directory tree with plenty of files, which are devlivered by server.


### Run
- add flag with path to resource directory
- add flag with database json path
- add flag with ip address if needed

If server, or engine do not respond you can find out logs in file: `client.txt`

## NGINX
<!-- TODO -->

## Create deb package
---
With using automated script in folder `scripts`:
```
sh create_deb.sh
```
Script will create folder `linuxconfig` and copy all files needed to create deb package, then with `dpkg-deb` tool  create `.deb` package in directory `out/`.

`linuxconfig` can be removed when `.deb` is created.

Files needed in `linuxconfig`:
```Cpp
+ linuxconfig/
    + DEBIAN/
        - control
    + usr/
        + bin/
            + piradio/
                - help.json
                - resources/
                - server
                - PiRadioApp
                - run.sh
    + etc/
        + systemd/
            + system/
                - piradio.service
```

Thats file are needed, but directory tree can be diffrent depends on deploy method.