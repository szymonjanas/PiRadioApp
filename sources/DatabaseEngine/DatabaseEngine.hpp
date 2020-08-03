#pragma once

#include <string>

#include "Station.hpp"

class DatabaseEngine {

public:
    virtual ~DatabaseEngine(){}

    virtual bool isLoad() = 0;
    virtual void load() = 0;
    virtual void save() = 0;

    virtual Station* getByName(std::string name) = 0;
    virtual Station* getByUri(std::string uri) = 0;
    virtual void put(Station* station) = 0;
    virtual void* getDatabase() = 0;
    virtual void remove(Station station) = 0;
    virtual std::string getNamesInString() = 0;
};
