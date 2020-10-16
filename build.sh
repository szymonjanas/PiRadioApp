#!/bin/bash

echo "BUILD ###########################################"
mkdir build
cd build

echo ""
echo "CMAKE ###########################################"
cmake ..

echo ""
echo "MAKE ############################################"
make

echo ""
echo "GO ##############################################"
go build -o server ../server/server.go ../server/log.go

cd ..

echo ""
echo "DONE ############################################"
echo ""
echo ""
