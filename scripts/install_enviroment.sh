#!/bin/bash

echo "C++ pack install"
echo ""
apt-get install -y g++ gcc cmake
echo ""
echo ""

echo "Gstreamer"
echo ""
apt-get install -y libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-pulseaudio
echo ""
echo ""

echo "ZMQ"
apt-get install -y libzmq5 libzmq3-dev
echo ""
echo ""

echo "Golang"
apt-get install -y golang
echo ""
echo "go get zmq4"
sudo -u $USER go get github.com/pebbe/zmq4
echo ""
echo ""

echo "Python3"
echo ""
apt-get install -y python3 python3-pip
sudo -u $USER pip3 install termcolor pyzmq
echo ""
echo ""

echo "gtest"
apt-get install -y libgtest-dev
cd /usr/src/gtest
cmake CMakeLists.txt
make
echo ""
echo ""

echo "DONE! ENVIROMENT INSTALLED." 
