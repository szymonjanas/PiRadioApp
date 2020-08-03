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

    if (args[0] == "station"){
        if (args[1] == "get"){
            if (args[2] == "all"){
                try {
                    if (!database->isLoad())
                        database->load();
                    reply = database->getNamesInString();
                } catch (std::string str){
                    reply = "error " + str;
                }
            } else if (args[2] == "current"){
                reply = manager->toString();
            } 
        } else if (args[1] == "delete"){
            database->remove(database->getByName(args[2]));
        } else if (args[1] == "set"){
            manager->setStation(database->getByName(args[2]));
            reply = Station::getString(manager->getStation());
        } else if (args[1] == "new"){
            database->put(new Station(args[2], args[3]));
        }
    } else if (args[0] == "engine"){
        if (args[1] == "state"){
            if (args[2] == "set"){
                manager->setState(args[3]);
            } else if (args[2] == "get"){
                reply = manager->getState();
            }
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
