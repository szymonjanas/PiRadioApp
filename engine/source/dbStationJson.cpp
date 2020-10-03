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
        for (auto iter = stations.begin(); iter != stations.end(); ++iter)
            this->put(new db::RECORD<std::string, radio::Station>((*iter)["name"], new radio::Station((*iter)["name"], (*iter)["uri"])));
        
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
            if (record == nullptr) return database[0]->getValue();
            for (int iter = 0; iter < database.size(); ++iter)
                if (database[iter]->getValue()->getName() == record->getName())
                    if (iter+1 < database.size())
                        return database[++iter]->getValue();
                    else
                        return database[0]->getValue();
        }   
        else if (database.size() == 1)
            return database[0]->getValue();
        else
            return nullptr;
     }

     radio::Station* StationsJson::getPrev(radio::Station* record)
     {
        if (database.size() > 1) {
            if (record == nullptr) return database[0]->getValue();
            for (int iter = database.size()-1; iter >= 0 ; --iter)
                if (database[iter]->getValue()->getName() == record->getName())
                    if (iter-1 >= 0)
                        return database[--iter]->getValue();
                    else 
                        return database[database.size()-1]->getValue();
        }
        else if (database.size() == 1)
            return database[0]->getValue();
        else
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
            jdata.push_back(record->getValue()->toJson());
        }
        return jdata;
    }

} // namespace db
