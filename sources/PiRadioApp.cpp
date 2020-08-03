#include <iostream>
#include <string>
#include "RadioManager.hpp"

int main(int argc, char ** argv)
{

    RadioManager *manager;

    bool debug = false;
    manager = new RadioManager(
        new StationsDatabaseTxt("../database.txt"),
        &AudioEngineManager::getManager(),
        new Communication(debug, "tcp://*:5555")
        );

    if (!debug)
        system("go run ../server/server.go &");

    manager->start();

    delete manager;
}
