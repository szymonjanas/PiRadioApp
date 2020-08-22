#include "Station.hpp"

Station::Station(std::string name, std::string uri) :
    name(name), uri(uri)
{}

std::string Station::getName() 
{
    return name;
}

std::string Station::getUri() 
{
    return uri;
}

void Station::setName(std::string name) 
{
    this->name = name;
}

void Station::setUri(std::string uri) 
{
    this->uri = uri;
}

std::string Station::toString() 
{
    return std::string(name + " " + uri);
}

bool Station::check(Station* station) 
{
    if (station == nullptr)
        return false;
    else 
        return true;
}

std::string Station::getString(Station* station) 
{
    std::string reply = "";
    if (check(station))
        reply = station->toString();
    else 
        reply = "Error StationDoesNotExist";
    return reply;
}

std::string Station::getName(Station* station) 
{
    if (check(station))
        return station->getName();
    else 
        return "StationDoesNotExist";
}

std::string Station::getUri(Station* station) 
{
    if (check(station))
        return station->getUri();
    else 
        return "StationDoesNotExist";
}
