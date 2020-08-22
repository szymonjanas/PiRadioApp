#pragma once

#include "Database.hpp"
#include "dbStationTxt.hpp"
#include "Communication.hpp"
#include "Audio.hpp"
#include "DebugMsg.hpp"

class RadioManager {

    Database* database;
    Audio::Manager* manager;
    Communication* communication;
    
public:
    RadioManager(   Database* database,
                    Audio::Manager* audioEngineManager,
                    Communication* communication);
    ~RadioManager();

    void setDatabase(Database* database);
    void setAudio(Audio::Manager* audioEngineManager);
    void setCommunication(Communication* communication);
    std::string execute(std::vector<std::string> command);
    void start();

};  
