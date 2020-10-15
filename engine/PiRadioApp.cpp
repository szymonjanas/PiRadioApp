#include <string>
#include <vector>
#include <iostream>

#include "json.hpp"

#include "Logs.hpp"
#include "Audio.hpp"
#include "AudioManager.hpp"
#include "RadioManager.hpp"
#include "dbStationJson.hpp"
#include "RadioRoutes.hpp"

void help(std::string);

int main(int argc, char **argv)
{
    bool helpFlag = false;
    bool onlyFlag = false;
    bool consoleFlag = false;
    bool audioFlag = true;

    std::string siteAddress = "";
    std::string internalCommunicationAddress = "ipc://piradio.app";
    std::string databasePath = "../database.json";

    std::string serverArgs = "";

    std::vector<std::string> args(argv, argv + argc);

    std::string argsStr = "";
    for (auto& argStr : args)
        argsStr += argStr + " ";
    Log::warn(argsStr);

    for (int i = 0, argvc = args.size(); i < argvc; ++i)
    {
        if (args[i] == "--help" or args[i] == "-h")
        {
            helpFlag = true;
            help("../help.json");
        }
        else if ((args[i] == "--icomm-address" or args[i] == "-ic") && i + 1 < argvc)
        {
            serverArgs += args[i] + " ";
            serverArgs += args[++i] + " ";
            internalCommunicationAddress = std::string(args[i]);
        }
        else if ((args[i] == "--icomm-port" or args[i] == "-icp") && i + 1 < argvc)
        {
            serverArgs += args[i] + " ";
            serverArgs += args[++i] + " ";
            internalCommunicationAddress = std::string(args[i]);
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
            Log::switches::debug(true);
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
            Log::warn("setted database: " + databasePath);
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
        else if (args[i] == "--no-audio" or args[i] == "-na")
        {
            audioFlag = false;
            Log::warn("No audio mode!");
        }
    }
    Log::warn("ARGS: " + serverArgs);

    if (!helpFlag)
    {

        Log::warn("Internal comm addr: " + internalCommunicationAddress);

        radio::Manager  *manager;

        radio::Audio    *audioManager;
        if (audioFlag) audioManager = new radio::Audio(new audio::Engine());
        else audioManager = new radio::Audio(new audio::EngineFake());
        
        db::StationsJson    *database = new db::StationsJson(databasePath);
        radio::Routes       *routes = new radio::Routes(database, audioManager);
        ipc::IPCService     *service = new ipc::IPCService();
        service->connect(internalCommunicationAddress);

        manager = new radio::Manager(
                        database,
                        audioManager,
                        service, 
                        routes
                    );

        if (!onlyFlag) {
            std::string str = "go run ../server/*.go " + serverArgs + " &";
            system(str.c_str());
        }

        manager->start();
        delete manager;
    }
    return 0;
}

void help(std::string helpPath)
{
    if (!helpPath.size()){
        Log::err("Help file path is empty!");
        throw std::string("Help file path is empty!");
    }
    std::fstream helpFile(helpPath, std::ios::in);
    if (!helpFile.good()){
        Log::err("Help file cannot be open: please check if json file exist!");
        throw std::string("Help file cannot be open: please check if json file exist!");
    }
    nlohmann::json dbJson = nlohmann::json::parse(helpFile);
    helpFile.close();

    auto stations = dbJson["help"];
    for (auto iter = stations.begin(); iter != stations.end(); ++iter)
        std::cout 
                << "  " << (*iter)["set"].get<std::string>() << "\n" 
                << "   " << (*iter)["short"].get<std::string>() << (((*iter)["short"].get<std::string>()).size() == 0 ? "" : "\n") 
                << "     " << (*iter)["description"].get<std::string>() << "\n"
                << "\n";

}
