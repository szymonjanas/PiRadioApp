#include <iostream>
#include <string>
#include "RadioManager.hpp"
#include "dbStationTxt.hpp"
#include "Audio.hpp"
#include "Logs.hpp"

int main(int argc, char ** argv)
{

    RadioManager *manager;

    bool debug = false;
    manager = new RadioManager(
        new db::StationsTxt("../database.txt"),
        &audio::Manager::getManager(),
        new Communication(debug, "tcp://*:5555")
        );

    if (!debug)
        system("go run ../server/server.go &");

    manager->start();

    delete manager;
    
    return 0;
}
