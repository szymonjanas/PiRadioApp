#pragma once

#include "Database.hpp"
#include "dbStationTxt.hpp"
#include "Communication.hpp"
#include "Audio.hpp"
#include "DebugMsg.hpp"

class RadioManager {

    Database* database;
    audio::Manager* manager;
    Engine* communication;
    
public:
    RadioManager(   Database* database,
                    audio::Manager* audioEngineManager,
                    Engine* communication);
    ~RadioManager();

    void setDatabase(Database* database);
    void setAudio(audio::Manager* audioEngineManager);
    void setCommunication(Engine* communication);
    std::string execute(std::vector<std::string> command);
    void start();

};  
