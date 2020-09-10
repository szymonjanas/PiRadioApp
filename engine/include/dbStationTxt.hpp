#pragma once

#include <vector>
#include <fstream>
#include <string>

#include "Database.hpp"

namespace db
{
    [[deprecated("Use json instead!")]]
    class StationsTxt : public Database<std::string, radio::Station>
    {
        bool loadFlag = false;
        std::string filePath;

    public:
        StationsTxt(std::string filePath);

        bool isLoad();
        virtual void load();
        virtual void save();

        virtual std::string toString(){return "";} 
        virtual nlohmann::json toJson(){return nlohmann::json();}

        virtual radio::Station* getNext(radio::Station* record);
        virtual radio::Station* getPrev(radio::Station* record);
    };

} // namespace db
