#include "dbStationJson.hpp"

namespace db {

    StationsJson::StationsJson(std::string filePath) : filePath(filePath) 
    {}

    StationsJson::~StationsJson() {

    }

    bool StationsJson::isLoad()
    {
        return loadFlag;
    }

    void StationsJson::load()
    {
        if (!filePath.size()){
            Log::err("Database file path is empty!");
            throw std::string("Database file path is empty!");
        }
        std::ifstream dbFile(filePath);
        if (!dbFile.good()){
            Log::err("Database cannot be open: please check if json file exist: " + filePath);
            throw std::string("Database cannot be open: please check if json file exist: " + filePath);
        }
        nlohmann::json dbJson = nlohmann::json::parse(dbFile);
        auto stations = dbJson["stations"];
        for (auto iter = stations.begin(); iter != stations.end(); ++iter){
            this->put(
                (*iter)["name"].get<std::string>(), 
                new radio::Station(
                    (*iter)["name"].get<std::string>(), 
                    (*iter)["uri"].get<std::string>()
                    )
                );
        }
        loadFlag = true;
        dbFile.close();
    }

     void StationsJson::save()
     {
        if (!filePath.size()){
            Log::err("Database file path is empty!");
            throw std::string("Database file path is empty!");
        }
        std::ofstream dbFile(filePath);
        if (!dbFile.good()){
            Log::err("Database cannot be open: please check if json file exist: " + filePath);
            throw std::string("Database cannot be open: please check if json file exist: " + filePath);
        }
        dbFile << toJson() << std::endl;
     }

     radio::Station* StationsJson::getNext(radio::Station* record)
     {
        
        if (database.size() > 1) {
            if (record == nullptr) return database.begin()->second.get();
            for (auto iter = database.begin(); iter != database.end(); ++iter)
                if (iter->second.get()->getName() == record->getName())
                    if ((++iter) != database.end())
                        return iter->second.get();
                    else
                        return database.begin()->second.get();
        }   
        else if (database.size() == 1)
            return database.begin()->second.get();
        return nullptr;
     }

     radio::Station* StationsJson::getPrev(radio::Station* record)
     {
        if (database.size() > 1) {
            if (record == nullptr) return database.begin()->second.get();
            for (auto iter = database.rbegin(); iter != database.rend() ; ++iter)
                if (iter->second.get()->getName() == record->getName())
                    if ((++iter) != database.rend())
                        return iter->second.get();
                    else 
                        return database.rbegin()->second.get();
            
        }
        else if (database.size() == 1)
            return database.begin()->second.get();
        return nullptr;
     }

    std::string StationsJson::toString()
    {
        return this->toJson().dump();
    }

    nlohmann::json StationsJson::toJson()
    {
        nlohmann::json jdata;
        for (auto& record : database){
            jdata.push_back(record.second.get()->toJson());
        }
        return jdata;
    }

} // namespace db
