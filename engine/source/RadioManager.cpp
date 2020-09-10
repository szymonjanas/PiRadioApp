#include "RadioManager.hpp"

namespace radio {

    Manager::Manager(db::Database<std::string, radio::Station> *database,
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

    void Manager::setDatabase(db::Database<std::string, radio::Station> *database)
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

        /* 
            Stations controller
        */
        if (args[0] == "isWorking"){
            reply = "working";
            Log::warn(reply);
            return reply;
        } 
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
                        reply = radio::Message(radio::Message::Type::REP, "Stations database").putValue(database->toJson()).toJson().dump();
                    }
                    catch (std::string str)
                    {
                        reply = radio::Message(radio::Message::Type::ERR, "Cannot load database: " + str).toJson().dump();
                        Log::err("Cannot load database: " + str);
                    }
                }
                else if (args[2] == "current")
                {
                    radio::Station *station = audio->getStation();
                    if (station == nullptr){
                        reply = radio::Message(radio::Message::Type::WARN, "No station loaded!").toJson().dump();
                        Log::warn("No station loaded!");
                    } 
                    else {
                        reply = station->toJson().dump();
                    }
                }
            }
            else if (args[1] == "remove")
            {
                if (database->getByID(args[2]) != nullptr)
                {
                    database->remove(database->getByID(args[2]));
                    reply = radio::Message(radio::Message::Type::INFO, "Station removed: " + args[2]).toJson().dump();
                    Log::info("Station removed: " + args[2]);
                }
                else
                {
                    reply = radio::Message(radio::Message::Type::ERR, "Station does not exist: " + args[2]).toJson().dump();
                    Log::err("Station does not exist: " + args[2]);
                }
            }
            else if (args[1] == "set")
            {
                if (database->getByID(args[2]) != nullptr)
                {
                    audio->setStation(database->getByID(args[2])->getValue());
                    reply = radio::Message(radio::Message::Type::INFO, "Station setted: " + audio->getStation()->getName()).toJson().dump();    
                }
                else
                {
                    reply = radio::Message(radio::Message::Type::ERR, "Station does not exist: " + args[2]).toJson().dump();
                    Log::err("Station does not exist: " + args[2]);
                }
            }
            else if (args[1] == "put")
            {
                try
                {
                    database->put(new db::RECORD<std::string, radio::Station>(args[2], new Station(args[2], args[3])));
                }
                catch (...)
                {
                    reply = radio::Message(radio::Message::Type::ERR, "Cannot add/change station: " + args[2]).toJson().dump();
                    Log::err("Cannot add/change station: " + args[2]);
                }
            }
            else if (args[1] == "switch")
            {
                Log::warn("SWITCH");
                if (args[2] == "prev") {
                    if (database->getDatabase() != nullptr) {
                        audio->setStation(
                                    database->getPrev(audio->getStation()));
                        reply = radio::Message(radio::Message::Type::INFO, "Prev station!").toJson().dump();
                        Log::debug("Prev station!");
                    } else {
                        reply = radio::Message(radio::Message::Type::ERR, "Cannot prev switch, database do not exist!").toJson().dump();
                        Log::err("Cannot prev switch, database do not exist!");
                    }
                }
                else if (args[2] == "next") {
                    if (database->getDatabase() != nullptr) {
                        audio->setStation(
                                    database->getNext(audio->getStation()));
                        reply = radio::Message(radio::Message::Type::INFO, "Next station!").toJson().dump();
                        Log::debug("Next station!");
                    } else {
                        reply = radio::Message(radio::Message::Type::ERR, "Cannot switch, database do not exist!").toJson().dump();
                        Log::err("Cannot switch, database do not exist!");
                    }
                }
            }
        }
        /*
            Engine controller
        */
        else if (args[0] == "engine")
        {
            if (args[1] == "state")
            {
                if (args[2] == "set")
                {
                    if (audio->canSetState(args[3]))
                    {
                        audio->setState(args[3]);
                        reply = radio::Message(radio::Message::Type::DEBUG, "Audio is: " + audio->getState()).toJson().dump();
                        Log::debug("Audio is:" + audio->getState() );
                    }
                    else
                    {
                        reply = radio::Message(radio::Message::Type::ERR, "Cannot set given state: " + args[3]).toJson().dump();
                        Log::err("Cannot set given state: " + args[3]);
                    }
                }
                else if (args[2] == "get")
                {
                    nlohmann::json jdata;
                    jdata["state"] = audio->getState();
                    reply = radio::Message(radio::Message::Type::REP, "State ").putValue(jdata).toJson().dump();
                }
            }
        }

        return reply;
    }

    void Manager::start()
    {
        Log::info("starting");
        while (true)
        {
            std::vector<std::string> args =
                    comm::convertStringsToArgs(
                        communication->recive());
            Log::warn("CONTROL r:" +args[0]);
            std::string reply = execute(args);
            Log::warn("CONTROL R:" + reply);
            communication->send(reply);
        }
    }

}
