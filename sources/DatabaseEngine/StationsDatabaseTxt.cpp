#include "StationsDatabaseTxt.hpp"

StationsDatabaseTxt::StationsDatabaseTxt(std::string filePath) :
    filePath(filePath)
{}

bool StationsDatabaseTxt::isLoad() 
{
    return (bool) database.size();
}

void StationsDatabaseTxt::load() 
{
    std::fstream dbFile(filePath, std::ios::in);
    if (!dbFile.good()) throw std::string("Cannot access file!");
    std::string record, name;
    bool nameFlag = true;
    while (std::getline(dbFile, record)){
        if (nameFlag) {
            name = record;
            nameFlag = false;
        } else {
            while (name.find('\r') != std::string::npos)
                name.erase(name.find('\r'));
            while (name.find('\n') != std::string::npos)
                name.erase(name.find('\n'));
            database.push_back(new Station(name, record));
            nameFlag = true;
        }
    }
    dbFile.close();
}

void StationsDatabaseTxt::save() 
{
    std::fstream dbFile("database.txt", std::ios::out);
	if (!dbFile.good()) throw std::string("Cannot save to file!");
	for (auto iter : database) {
        dbFile << iter->getName() + "\n";
		dbFile << iter->getUri() + "\n";
	}
	dbFile.close();
}

Station* StationsDatabaseTxt::getByName(std::string name) 
{
    for (auto iter : database)
        if (iter->getName() == name) return iter;
    return nullptr;
}

Station* StationsDatabaseTxt::getByUri(std::string uri) 
{
    for (auto iter : database)
        if (iter->getUri() == uri) return iter;
    return nullptr;
}

void StationsDatabaseTxt::put(Station* station)
{
    if (station == nullptr) return;
    if (getByName(station->getName()) != nullptr)
        getByName(station->getName())->setUri(station->getUri());
    else 
        database.push_back(station);
    this->save();
}

void* StationsDatabaseTxt::getDatabase() 
{
    return reinterpret_cast<void*>(&database);
}

void StationsDatabaseTxt::remove(Station* station) 
{
    if (station == nullptr) return;
    for (auto iter = database.begin(); iter != database.end(); )
        if ((*iter)->getName() == station->getName())
            database.erase(iter);
        else 
            ++iter;
    this->save();
}

std::string StationsDatabaseTxt::getNamesInString() 
{
    std::string all = "";
    for (auto iter : database)
        all += iter->getName() + " ";    
    return all;
}
