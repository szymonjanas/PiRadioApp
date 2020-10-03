#pragma once

#include "json.hpp"

#include "Database.hpp"
#include "dbStationJson.hpp"
#include "Communication.hpp"
#include "Logs.hpp"
#include "AudioManager.hpp"
#include "RadioCommMessage.hpp"
#include "RadioIPCMessage.hpp"
#include <stdlib.h>

namespace radio {

    class Manager
    {
        /*
            Recive and process message in json format:
            {
                "method" : "get",
                "layer" : "engine",
                "command" : "play",
                "value" : ""
            }
        */


        db::Database<std::string, radio::Station> *database;
        radio::Audio *audio;
        comm::Engine *communication;

    public:
        Manager(db::Database<std::string, radio::Station> *database,
                     radio::Audio *audio,
                     comm::Engine *communication);
        ~Manager();

        void setDatabase(db::Database<std::string, radio::Station> *database);
        void setAudio(radio::Audio *audioEngineManager);
        void setCommunication(comm::Engine *communication);
        std::string execute(radio::IPCMessage&& message);
        void start();
    };

}
