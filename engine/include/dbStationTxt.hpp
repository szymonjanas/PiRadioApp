#pragma once

#include <vector>
#include <fstream>
#include <string>

#include "Database.hpp"

namespace db
{
    class StationsTxt : public Database<radio::Station, std::string>
    {

        std::vector<radio::Station *> database;
        std::string filePath;

    public:
        StationsTxt(std::string filePath);

        bool isLoad();
        virtual void load();
        virtual void save();

        virtual radio::Station *getByID(std::string name);
        virtual void put(radio::Station *station);
        virtual void *getDatabase();
        virtual void remove(radio::Station *station);
        virtual std::string getIDsInString();
    };

} // namespace db
