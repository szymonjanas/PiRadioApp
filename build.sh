#!/bin/bash

echo "BUILD ###########################################"
mkdir build

echo ""
echo "CMAKE ###########################################"
cmake -H. -Bbuild/

echo ""
echo "MAKE ############################################"
make -C build/

echo ""
echo "GO ##############################################"
go build -o build/server server/server.go server/log.go


echo ""
echo "DONE ############################################"
echo ""
echo ""
