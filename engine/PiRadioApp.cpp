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
    
    log::switches::color(true);

    manager = new RadioManager(
        new db::StationsTxt("../database.txt"),
        &audio::Manager::getManager(),
        new comm::Engine("tcp://*:5555", debug)
        );

    if (!debug)
        system("go run ../server/server.go &");

    manager->start();

    delete manager;
    
    return 0;
}
