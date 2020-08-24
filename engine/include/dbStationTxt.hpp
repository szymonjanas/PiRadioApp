#pragma once

#include <vector>
#include <fstream>
#include <string>

#include "Database.hpp"

namespace db
{
    class StationsTxt : public Database<Station, std::string>
    {

        std::vector<Station *> database;
        std::string filePath;

    public:
        StationsTxt(std::string filePath);

        bool isLoad();
        virtual void load();
        virtual void save();

        virtual Station *getByID(std::string name);
        virtual void put(Station *station);
        virtual void *getDatabase();
        virtual void remove(Station *station);
        virtual std::string getIDsInString();
    };

} // namespace db
