#include <iostream>
#include <string>
#include "RadioManager.hpp"
#include "DebugMsg.hpp"

std::string help();

int main(int argc, char *argv[])
{
    bool helpFlag = false;
    bool onlyFlag = false;
    bool consoleFlag = false;


    std::string siteAddress = "";
    std::string internalCommunicationAddress = "tcp://";

    std::string args[argc];
    for (int i = 0; i < argc; ++i)
        args[i] = std::string(argv[i]);

    for (int i = 0; i < argc; ++i){
        if (args[i] == "--help" or args[i] == "-h") {
            helpFlag = true;
            std::cout << help();
        } else if ((args[i] == "--internal-communication-address" or args[i] == "-ic") and i+1 < argc){
            internalCommunicationAddress += std::string(args[++i]); ++i;
        } else if ((args[i] == "--internal-communication-port" or args[i] == "-icp") and i+1 < argc){
            internalCommunicationAddress += "localhost:" + std::string(args[++i]); ++i;
        } else if ((args[i] == "--host-address" or args[i] == "-h") and i+1 < argc){
            siteAddress = std::string(args[++i]); ++i;
        } else if ((args[i] == "--host-port" or args[i] == "-hp") and i+1 < argc){
            siteAddress = ":" + std::string(args[++i]); ++i;
        } else if ((args[i] == "--resource" or args[i] == "-res") and i+1 < argc){
            
        } else if ((args[i] == "--host-url" or args[i] == "-url") and i+1 < argc){
            
        } else if ((args[i] == "--host-api-url" or args[i] == "-aurl") and i+1 < argc){
            
        } else if (args[i] == "--debug" or args[i] == "-d"){

        } else if (args[i] == "--only"){
            onlyFlag = true;
        } else if (args[i] == "--only-with-console"){
            debug::info("Mode: Only with console. Internal communication turned off. Type \"help\" for instructions.");
            onlyFlag = true;
            consoleFlag = true;
        }
    }
    if (!helpFlag){

        RadioManager *manager;

        manager = new RadioManager(
            new StationsDatabaseTxt("../database.txt"),
            &AudioEngineManager::getManager(),
            new Communication(consoleFlag, "tcp://*:5555") 
            );

        if (!onlyFlag)
            system("go run ../server/server.go &");

        manager->start();

        delete manager;
    }
}

std::string help() 
{
    std::string helpStr = "";
        helpStr += "PiRadio help sheet\n";
        helpStr += " * Internal (server <-> engine) tcp communication address. Default: localhost:5555 \n";
        helpStr += "       --internal-communication-address [ip:port]\n";
        helpStr += "       -ic [ip:port]\n";
        helpStr += "   Internal (server <-> engine) tcp communication port. Default: 5555 \n";
        helpStr += "       --internal-communication-port [port] \n";
        helpStr += "       -icp [port] \n";
        helpStr += " * Host site address. Default: localhost:8080 \n";
        helpStr += "       --host-address [ip:port] \n";
        helpStr += "       -h [ip:port] \n";
        helpStr += "   Host site port. Default: 8080 \n ";
        helpStr += "       --host-port [port] \n";
        helpStr += "       -hp [port]\n";
        helpStr += " * Resource relative path. Default: /static/ \n";
        helpStr += "       --resource [path]\n";
        helpStr += "       -res [path]\n";
        helpStr += " * Host site url path. Default: /radio/ \n";
        helpStr += "       --host-url [path]\n";
        helpStr += "       -url [path]\n";
        helpStr += " * Host api url path. Default: /api/radio/ \n";
        helpStr += "       --host-api-url [path]\n";
        helpStr += "       -aurl [path]\n";
        helpStr += " * Debug mode. \n";
        helpStr += "       --debug \n";
        helpStr += "       -d \n";
        helpStr += " * Run only engine app. \n";
        helpStr += "       --only \n";
        helpStr += " * Run only engine app with controlling from console instead of internal communication tcp \n";
        helpStr += "       Mode for testing purpose. \n";
        helpStr += "       --only-with-console \n";
        helpStr += "\n \n";
    return helpStr;
}
