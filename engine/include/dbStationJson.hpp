#pragma once

#include "Database.hpp"
#include "Station.hpp"

#include <fstream>
#include <string>
#include "json.hpp"
#include "Logs.hpp"

namespace db {

    class StationJson : public db::Database<std::string, radio::Station> {

        bool loadFlag = false;
        std::string filePath;
        
    public:

        StationJson(std::string filePath);
        ~StationJson();

        virtual bool isLoad();
        virtual void load();
        virtual void save();

        virtual radio::Station* getNext(radio::Station* record);
        virtual radio::Station* getPrev(radio::Station* record);

    };

} // namespace db
