#include <string>
#include <vector>
#include <iostream>
#include "RadioManager.hpp"
#include "dbStationTxt.hpp"
#include "dbStationJson.hpp"
#include "AudioManager.hpp"
#include "Audio.hpp"
#include "Logs.hpp"

std::string help();

int main(int argc, char **argv)
{
    bool helpFlag = false;
    bool onlyFlag = false;
    bool consoleFlag = false;

    std::string siteAddress = "";
    std::string internalCommunicationAddress = "ipc://piradio.app";
    std::string databasePath = "../database.json";

    std::string serverArgs = "";

    std::vector<std::string> args(argv, argv + argc);
    for (int i = 0, argvc = args.size(); i < argvc; ++i)
    {
        if (args[i] == "--help" or args[i] == "-h")
        {
            helpFlag = true;
            std::cout << help();
        }
        else if ((args[i] == "--icomm-address" or args[i] == "-ic") && i + 1 < argvc)
        {
            serverArgs += args[i] + " ";
            serverArgs += args[++i] + " ";
            internalCommunicationAddress = "tcp://" + std::string(args[i]);
        }
        else if ((args[i] == "--icomm-port" or args[i] == "-icp") && i + 1 < argvc)
        {
            serverArgs += args[i] + " ";
            serverArgs += args[++i] + " ";
            internalCommunicationAddress = "tcp://*:" + std::string(args[i]);
        }
        else if ((args[i] == "--host-address" or args[i] == "-h") && i + 1 < argvc)
        {
            serverArgs += args[i] + " ";
            serverArgs += args[++i] + " ";
        }
        else if ((args[i] == "--host-port" or args[i] == "-hp") && i + 1 < argvc)
        {   
            serverArgs += args[i] + " ";
            serverArgs += args[++i] + " ";
        }
        else if ((args[i] == "--resource" or args[i] == "-res") && i + 1 < argvc)
        {
            serverArgs += args[i] + " ";
            serverArgs += args[++i] + " ";
        }
        else if (args[i] == "--debug" or args[i] == "-d")
        {
            serverArgs += (args[i] + " ");
        }
        else if (args[i] == "--only")
        {
            onlyFlag = true;
        }
        else if (args[i] == "--only-with-console")
        {
            Log::warn("Mode: Only with console. Internal communication turned off. Type \"help\" for instructions.");
            onlyFlag = true;
            consoleFlag = true;
        }
        else if ((args[i] == "--database" or args[i] == "-db") and i + 1 < argc)
        {
            databasePath = args[++i];
        }
        else if (args[i] == "--cmd-colors" or args[i] == "-col")
        {
            serverArgs += args[i] + " ";
            Log::switches::color(true);
        }
        else if (args[i] == "--basic-cmd" or args[i] == "-b")
        {
            serverArgs += args[i] + " ";
            Log::switches::basic(true);
        }
    }
    Log::warn("ARGS: " + serverArgs);

    if (!helpFlag)
    {

        Log::warn("Internal comm addr: " + internalCommunicationAddress);

        radio::Manager *manager;

        comm::Engine *commEngine = new comm::Engine(internalCommunicationAddress, consoleFlag);

        manager = new radio::Manager(
                    new db::StationsJson(databasePath),
                    new radio::Audio(new audio::Engine()),
                    commEngine );

        if (!onlyFlag) {
            std::string str = "go run ../server/*.go " + serverArgs + " &";
            system(str.c_str());
        }

        manager->start();
        delete manager;
    }
    return 0;
}

std::string help() 
{
    std::string helpStr = "";
    helpStr += "PiRadio help sheet\n";
    helpStr += "\n";
    helpStr += " --icomm-address [ip:port]  Internal (server <-> engine) tcp communication address. \n";
    helpStr += "    -ic [ip:port]               Default: localhost:5555\n";
    helpStr += " --icomm-port [port]        Internal (server <-> engine) tcp communication port. \n";
    helpStr += "    -icp [port]                 Default: 5555 \n";
    helpStr += "\n";
    helpStr += " --host-address [ip:port]   Host site address.  \n";
    helpStr += "    -h [ip:port]                Default: localhost:8080\n";
    helpStr += " --host-port [port]         Host site port.  \n";
    helpStr += "    -hp [port]                  Default: 8080\n";
    helpStr += "\n";
    helpStr += " --resource [path]          Resource path.  \n";
    helpStr += "    -res [path]                 Default: ../server/resources/\n";
    helpStr += "\n";
    helpStr += " --debug                    Debug mode \n";
    helpStr += "    -d \n";
    helpStr += "\n";
    helpStr += " --only                     Run only engine app \n";
    helpStr += " --only-with-console        Run only engine app with cmd control instead of internal communication tcp  \n";
    helpStr += "                                Mode for testing purpose \n";
    helpStr += "\n";
    helpStr += " --database [path]          Set database path \n";
    helpStr += "    -db [path] \n";
    helpStr += "\n";
    helpStr += " --cmd-colors               Enable colors of console message \n";
    helpStr += "       -col \n";
    helpStr += " --basic-cmd                Disable info and debug message.\n";
    helpStr += "    -b \n";
    helpStr += "\n \n";
    return helpStr;
}
