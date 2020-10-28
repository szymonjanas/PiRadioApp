#!/bin/bash

echo "BUILD ###########################################"
cd ..
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
cd scripts

echo ""
echo "ALL CASES BUILD! ############################################"
echo ""
echo ""
