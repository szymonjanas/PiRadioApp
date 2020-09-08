#pragma once

#include <vector>
#include <fstream>
#include <string>

#include "Database.hpp"

namespace db
{
    class StationsTxt : public Database<std::string, radio::Station>
    {
        bool loadFlag = false;
        std::string filePath;

    public:
        StationsTxt(std::string filePath);

        bool isLoad();
        virtual void load();
        virtual void save();

        virtual std::string getIDsInString(){return "";}

        virtual radio::Station* getNext(radio::Station* record);
        virtual radio::Station* getPrev(radio::Station* record);
    };

} // namespace db
