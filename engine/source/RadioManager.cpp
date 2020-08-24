#include "RadioManager.hpp"

RadioManager::RadioManager(db::Database *database,
                           audio::Manager *audioEngineManager,
                           comm::Engine *communication) : database(database),
    manager(audioEngineManager),
    communication(communication)
{
}

RadioManager::~RadioManager()
{
    delete database;
    delete communication;
}

void RadioManager::setDatabase(db::Database *database)
{
    this->database = database;
}

void RadioManager::setAudio(audio::Manager *audioEngineManager)
{
    this->manager = audioEngineManager;
}

void RadioManager::setCommunication(comm::Engine *communication)
{
    this->communication = communication;
}

std::string RadioManager::execute(std::vector<std::string> args)
{
    std::string reply = "error command not found";

    if (args[0] == "station")
    {
        if (args[1] == "get")
        {
            if (args[2] == "all")
            {
                try
                {
                    if (!database->isLoad())
                        database->load();
                    reply = database->getNamesInString();
                }
                catch (std::string str)
                {
                    reply = "err Error, Cannot load database: " + str;
                    log::err("Cannot load database: " + str);
                }
            }
            else if (args[2] == "current")
                reply = manager->toString();
        }
        else if (args[1] == "remove")
        {
            if (database->getByName(args[2]) != nullptr)
            {
                database->remove(database->getByName(args[2]));
                reply = "msg Station removed: " + args[2];
            }
            else
            {
                reply = "err Station does not exist: " + args[2];
                log::err(reply);
            }
        }
        else if (args[1] == "set")
        {
            if (database->getByName(args[2]) != nullptr)
            {
                manager->setStation(database->getByName(args[2]));
                reply = "msg Station setted: " + manager->getStation()->getName();
            }
            else
            {
                reply = "err Station does not exist: " + args[2];
                log::err(reply);
            }
        }
        else if (args[1] == "new")
        {
            try
            {
                database->put(new Station(args[2], args[3]));
            }
            catch (...)
            {
                reply = "err Somethink went wrong!";
                log::err(reply);
            }
        }
    }
    else if (args[0] == "engine")
    {
        if (args[1] == "state")
        {
            if (args[2] == "set")
            {
                if (manager->canSetState(args[3]))
                {
                    manager->setState(args[3]);
                    reply = "msg Audio is: " + manager->getState();
                }
                else
                    reply = "err Cannot set given state: " + args[3];
            }
            else if (args[2] == "get")
            {
                reply = manager->getState();
            }
        }
    }

    return reply;
}

void RadioManager::start()
{
    log::info("starting");
    while (true)
    {
        std::vector<std::string> args =
                comm::convertStringsToArgs(
                    communication->recive());
        std::string reply = execute(args);
        communication->send(reply);
    }
}
