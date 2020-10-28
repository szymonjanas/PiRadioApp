[Main](README.md)

**Installation guide for: Ubuntu (also WSL), Mint, Raspbian.**

_WARNING: Audio is not working on WSL!_
# Developement version installation guide:
## Install

1. **C/C++** `sudo apt install g++ gcc cmake`
2. **Gstreamer** `sudo apt-get install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-pulseaudio`
3. **Golang** `sudo apt install golang`
4. **ZMQ Lib** `sudo apt install libzmq5 libzmq3-dev`
5. **ZMQ for golang** `go get github.com/pebbe/zmq4`
6. **uTests** 
   1. `sudo apt install libgtest-dev`
   2. `cd /usr/src/gtest`
   3. `sudo cmake CMakeLists.txt`
   4. `sudo make`
   5. go back to project folder
***

## Run
1. in project directory (where CMakeLists.txt is)
2. `mkdir build && cd build` - separate folder to build,
3. `cmake .. && make` - build with cmake (compiling and linking),
4. `go build -o server ../server/*.go` - build server 
5. `./PiRadioApp` - run application,
**In current version recompile is needed only when C++ files were changed!**

**uTests:** After build project we can run uTests with `./PiRadioApp-engine-utests`

*** 
## Intergrations Tests
### Install
First you must do the previous steps.
1. `sudo apt install python3.6 python3-pip` - install python at least ver 3.6
2. `pip3 install setuptools pyzmq termcolor`
### Run
1. `python3 tests/` - run tests, call from main project folder (should be there also folders `build` and `tests`)
