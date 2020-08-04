#pragma once

#include "DatabaseEngine.hpp"
#include "StationsDatabaseTxt.hpp"
#include "Communication.hpp"
#include "AudioEngineManager.hpp"
#include "DebugMsg.hpp"

class RadioManager {

    DatabaseEngine* database;
    AudioEngineManager* manager;
    Communication* communication;
    
public:
    RadioManager(   DatabaseEngine* database,
                    AudioEngineManager* audioEngineManager,
                    Communication* communication);
    ~RadioManager();

    void setDatabase(DatabaseEngine* database);
    void setAudio(AudioEngineManager* audioEngineManager);
    void setCommunication(Communication* communication);
    std::string execute(std::vector<std::string> command);
    void start();

};  
