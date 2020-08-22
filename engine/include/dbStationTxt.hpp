#pragma once

#include <vector>
#include <fstream>
#include <string>

#include "Database.hpp"

namespace db
{
    class StationsTxt : public Database
    {

        std::vector<Station *> database;
        std::string filePath;

    public:
        StationsTxt(std::string filePath);

        bool isLoad();
        virtual void load();
        virtual void save();

        virtual Station *getByName(std::string name);
        virtual Station *getByUri(std::string uri);
        virtual void put(Station *station);
        virtual void *getDatabase();
        virtual void remove(Station *station);
        virtual std::string getNamesInString();
    };

} // namespace db