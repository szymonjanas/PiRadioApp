#include "RadioManager.hpp"

namespace radio {

    Manager::Manager(db::Database<radio::Station, std::string> *database,
                     radio::Audio *audio,
                     comm::Engine *communication) : database(database),
        audio(audio),
        communication(communication)
    {}

    Manager::~Manager()
    {
        delete audio;
        delete database;
        delete communication;
    }

    void Manager::setDatabase(db::Database<Station, std::string> *database)
    {
        this->database = database;
    }

    void Manager::setAudio(radio::Audio *audioEngineManager)
    {
        this->audio = audioEngineManager;
    }

    void Manager::setCommunication(comm::Engine *communication)
    {
        this->communication = communication;
    }

    std::string Manager::execute(std::vector<std::string> args)
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
                        reply = database->getIDsInString();
                    }
                    catch (std::string str)
                    {
                        reply = "err Error, Cannot load database: " + str;
                        log::err("Cannot load database: " + str);
                    }
                }
                else if (args[2] == "current")
                    reply = audio->toString();
            }
            else if (args[1] == "remove")
            {
                if (database->getByID(args[2]) != nullptr)
                {
                    database->remove(database->getByID(args[2]));
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
                if (database->getByID(args[2]) != nullptr)
                {
                    audio->setStation(database->getByID(args[2]));
                    reply = "msg Station setted: " + audio->getStation()->getName();
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
                    if (audio->canSetState(args[3]))
                    {
                        audio->setState(args[3]);
                        reply = "msg Audio is: " + audio->getState();
                    }
                    else
                        reply = "err Cannot set given state: " + args[3];
                        log::warn(reply);
                }
                else if (args[2] == "get")
                {
                    reply = audio->getState();
                }
            }
        }

        return reply;
    }

    void Manager::start()
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

}
