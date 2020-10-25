#!/bin/bash

echo "BUILD ###########################################"
mkdir build
cd build

echo ""
echo "cmake ###########################################"
cmake ..

echo ""
echo "make ############################################"
make -j4

echo ""
echo "golang ##############################################"
go build -o server ../server/server.go ../server/log.go

cd ..

echo ""
echo "DONE ############################################"
echo ""
echo ""
