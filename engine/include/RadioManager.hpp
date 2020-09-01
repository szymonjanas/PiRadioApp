#pragma once

#include "Database.hpp"
#include "dbStationTxt.hpp"
#include "Communication.hpp"
#include "Logs.hpp"
#include "AudioManager.hpp"

namespace radio {

    class Manager
    {

        db::Database<radio::Station, std::string> *database;
        radio::Audio *audio;
        comm::Engine *communication;

    public:
        Manager(db::Database<radio::Station, std::string> *database,
                     radio::Audio *audio,
                     comm::Engine *communication);
        ~Manager();

        void setDatabase(db::Database<Station, std::string> *database);
        void setAudio(radio::Audio *audioEngineManager);
        void setCommunication(comm::Engine *communication);
        std::string execute(std::vector<std::string> command);
        void start();
    };



}
