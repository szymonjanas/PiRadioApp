#include "RadioManager.hpp"

RadioManager::RadioManager(DatabaseEngine* database,
                    AudioEngineManager* audioEngineManager,
                    Communication* communication) :
    database(database), 
    manager(audioEngineManager), 
    communication(communication)
{}

RadioManager::~RadioManager() 
{
    delete database;
    delete communication;
}

void RadioManager::setDatabase(DatabaseEngine* database) 
{
    this->database = database;
}

void RadioManager::setAudio(AudioEngineManager* audioEngineManager) 
{
    this->manager = audioEngineManager;
}

void RadioManager::setCommunication(Communication* communication) 
{
    this->communication = communication;
}

std::string RadioManager::execute(std::vector<std::string> args) 
{
    std::string reply = "error command not found";

    if (args[0] == "set"){

        if (args[1] == "state"){
            manager->setState(args[2]);
            reply = manager->getState();
        } 
        
        else if (args[1] == "station") {
            manager->setStation(database->getByName(args[2]));
            reply = Station::getString(manager->getStation());
        }
    }

    else if (args[0] == "get"){

        if (args[1] == "station"){

            if (args[2] == "all"){
                try {
                    if (!database->isLoad())
                        database->load();
                    reply = database->getNamesInString();
                } catch (std::string str){
                    reply = "error " + str;
                }
            }
            else if (args[2] == "current")
                reply = Station::getString(manager->getStation());
            else
                reply = Station::getString(database->getByName(args[2]));

        } 

        else if (args[1] == "state"){
            reply = manager->getState();
        } 

        else if (args[1] == "details") {
            reply = manager->getDetails(args[2]);
        } 
    }

    return reply;
}

void RadioManager::start() 
{
    while (true) {
        std::cout << "starting" << std::endl;
        std::vector<std::string> args = 
            communication->convertStringsToArgs(
                communication->recive()
                );
        std::cout << "reciv" << std::endl;

        std::string reply = execute(args);

        communication->send(reply);
    }
}
