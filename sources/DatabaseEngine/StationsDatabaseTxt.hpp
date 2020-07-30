#pragma once

#include <vector>
#include <fstream>
#include <string>

#include "StationsDatabaseInterface.hpp"

class StationsDatabaseTxt : public StationsDatabaseInterface {

    std::vector<Station*> database;
    std::string filePath;
public:

    StationsDatabaseTxt(std::string filePath);

    virtual void load();
    virtual void save();

    virtual Station* getByName(std::string name);
    virtual Station* getByUri(std::string uri);
    virtual void put(Station* station);
    virtual void* getDatabase();
    virtual void remove(Station station);
    virtual std::string getNamesInString();

};
