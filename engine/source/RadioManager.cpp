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

    std::string Manager::execute(radio::IPCMessage&& message)
    {
        nlohmann::json reply;

        /* 
            Stations controller
        */
        switch (message.applies){
        case radio::IPCMessage::APPLIES::DATABASE:

            switch (message.type) { 
            case radio::IPCMessage::TYPE::GET: 
            {
                if (message.command == "all") {
                    try
                    {
                        if (!database->isLoad())
                            database->load();
                        reply = radio::Message(radio::Message::Type::REP, "Stations database").putValue(database->toJson()).toJson();
                    }
                    catch (std::string str)
                    {
                        std::string homedir = getenv("HOME");
                        Log::info("HOMEDIR " + homedir);
                        delete database;
                        homedir += "/radio-database.json";
                        database = new db::StationsJson(homedir);
                        database->save();
                        reply = radio::Message(radio::Message::Type::ERR, "Cannot load database: " + str + ". CREATED NEW DATABASE: " + homedir).toJson();
                        Log::err("Cannot load database: " + str + ". CREATED NEW DATABASE: " + homedir);
                    }
                } 
            }
            break;   

            case radio::IPCMessage::TYPE::PUT:
            {
                radio::Station &station = message.station;
                try
                {
                    database->put(new db::RECORD<std::string, radio::Station>(station.getName(), new Station(station)));
                    reply = radio::Message(radio::Message::Type::INFO, "Station added to database: " + station.getName() + " " + station.getUri()).toJson();
                    Log::info("Station added to database: " + station.getName() + " " + station.getUri());
                }
                catch (...)
                {
                    reply = radio::Message(radio::Message::Type::ERR, "Cannot add/change station: " + station.getName()).toJson();
                    Log::err("Cannot add/change station: " + station.getName());
                }
            }
            break;

            case radio::IPCMessage::TYPE::DELETE:
            {
                std::string id = message.station.getName();
                if (database->getByID(id) != nullptr)
                {
                    database->remove(database->getByID(id));
                    reply = radio::Message(radio::Message::Type::INFO, "Station deleted: " + id).toJson();
                    Log::info("Station deleted: " + id);
                }
                else
                {
                    reply = radio::Message(radio::Message::Type::ERR, "Station does not exist: " + id).toJson();
                    Log::err("Station does not exist: " + id);
                }
            }
            break;

            }        
        break;

        case radio::IPCMessage::APPLIES::AUDIO:
            switch(message.type){
            case radio::IPCMessage::TYPE::SWITCH:
                Log::warn("SWITCH");
                if (message.command == "prev") {
                    if (database->getDatabase() != nullptr) {
                        audio->setStation(
                                    database->getPrev(audio->getStation()));
                        reply = radio::Message(radio::Message::Type::INFO, "Prev station!").toJson();
                        Log::debug("Prev station!");
                    } else {
                        reply = radio::Message(radio::Message::Type::ERR, "Cannot prev switch, database do not exist!").toJson();
                        Log::err("Cannot prev switch, database do not exist!");
                    }
                }
                else if (message.command == "next") {
                    if (database->getDatabase() != nullptr) {
                        audio->setStation(
                                    database->getNext(audio->getStation()));
                        reply = radio::Message(radio::Message::Type::INFO, "Next station!").toJson();
                        Log::debug("Next station!");
                    } else {
                        reply = radio::Message(radio::Message::Type::ERR, "Cannot switch, database do not exist!").toJson();
                        Log::err("Cannot switch, database do not exist!");
                    }
                }
            break;

            case radio::IPCMessage::TYPE::SET:
            {
                if (message.command == "state") {
                    std::string cmd = message.command;
                    if (audio->canSetState(cmd))
                    {
                        //! HERE STATE WORD NEEDS TO BE REMOVED FROM COMMAND
                          

                        audio->setState(cmd);
                        reply = radio::Message(radio::Message::Type::INFO, "Audio is: " + radio::Audio::stateToString(audio->getState())).toJson();
                        Log::debug("Audio is:" + radio::Audio::stateToString(audio->getState()));
                    }
                    else
                    {
                        reply = radio::Message(radio::Message::Type::ERR, "Cannot set given state: " + cmd).toJson().dump();
                        Log::err("Cannot set given state: " + cmd);
                    }
                } 
                else if (message.command == "station") {
                    std::string id = message.station.getName();
                    if (id.size() > 0 && database->getByID(id) != nullptr)
                    {
                        audio->setStation(database->getByID(id)->getValue());
                        if (message.command == "play")
                            audio->setState(audio::STATE::PLAY);
                        else if (message.command == "stop")
                            audio->setState(audio::STATE::STOP);
                        reply = radio::Message(radio::Message::Type::INFO, "Station setted and playing: " + audio->getStation()->getName()).toJson();
                        Log::info("Setted and play: " + id);    
                    }
                    else
                    {
                        reply = radio::Message(radio::Message::Type::ERR, "Station does not exist: " + id).toJson();
                        Log::err("Station does not exist: " + id);
                    }
                }
            }
            break;

            case radio::IPCMessage::TYPE::GET:
            {
                if (message.command == "state") {
                nlohmann::json jdata;
                jdata["state"] = audio->getState();
                reply = radio::Message(radio::Message::Type::REP, "State ").putValue(jdata).toJson();

                } else if (message.command == "current") {
                    radio::Station *station = audio->getStation();
                    if (station == nullptr){
                        reply = radio::Message(radio::Message::Type::WARN, "No station loaded!").toJson();
                        Log::warn("No station loaded!");
                    } 
                    else {
                        reply = station->toJson();
                    }
                }
            }
            break;

            }
        }
        return reply.dump();
    }

    void Manager::start()
    {
        Log::info("starting");
        while (true)
        {
            std::string request = communication->recive();
            std::string reply = execute(radio::IPCMessage(request));
            communication->send(reply);
        }
    }

} // namespace radio
