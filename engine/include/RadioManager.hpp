#pragma once

#include <string>
#include "json.hpp"
#include "Database.hpp"
#include "dbStationJson.hpp"
#include "Logs.hpp"
#include "RadioStation.hpp"
#include "AudioManager.hpp"
#include "ipc/IPCService.hpp"
#include "ipc/IPCRoutes.hpp"

// #include <stdlib.h>

namespace radio {

    class Manager
    {

        db::Database<std::string, radio::Station> *database;
        radio::Audio *audio;
        ipc::IPCService *service;
        ipc::IPCRoutes *routes;

        public:
        Manager(db::Database<std::string, radio::Station> *database,
                radio::Audio *audio,
                ipc::IPCService *service,
                ipc::IPCRoutes *routes);
        ~Manager();

        void setDatabase(db::Database<std::string, radio::Station> *database);
        void setAudio(radio::Audio *audioEngineManager);
        void setService(ipc::IPCService *service);
        void setRoutes(ipc::IPCRoutes *routes);
        void start();
    };

}
