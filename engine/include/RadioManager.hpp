#pragma once

#include "Database.hpp"
#include "dbStationTxt.hpp"
#include "Communication.hpp"
#include "Logs.hpp"
#include "AudioManager.hpp"

namespace radio {

    class Manager
    {

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
        std::string execute(std::vector<std::string> command);
        void start();
    };



}
