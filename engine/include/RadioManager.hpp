#pragma once

#include "Database.hpp"
#include "dbStationTxt.hpp"
#include "Communication.hpp"
#include "Audio.hpp"
#include "Logs.hpp"

class RadioManager
{

    db::Database *database;
    audio::Manager *manager;
    comm::Engine *communication;

public:
    RadioManager(db::Database *database,
                 audio::Manager *audioEngineManager,
                 comm::Engine *communication);
    ~RadioManager();

    void setDatabase(db::Database *database);
    void setAudio(audio::Manager *audioEngineManager);
    void setCommunication(comm::Engine *communication);
    std::string execute(std::vector<std::string> command);
    void start();
};
