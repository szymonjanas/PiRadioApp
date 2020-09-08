#include "dbStationJson.hpp"

namespace db {

    StationJson::StationJson(std::string filePath) : filePath(filePath) 
    {}

    StationJson::~StationJson() {

    }

    bool StationJson::isLoad()
    {
        return loadFlag;
    }

    void StationJson::load()
    {
        if (!filePath.size()){
            Log::err("Database file path is empty!");
            return;
        }
        std::fstream dbFile(filePath, std::ios::in);
        if (!dbFile.good()){
            Log::err("Database cannot be open: please check if json file exist!");
            return;
        }
        nlohmann::json dbJson = nlohmann::json::parse(dbFile);
        auto stations = dbJson["stations"];
        for (auto iter = stations.begin(); iter != stations.end(); ++iter){
            this->put(new db::RECORD<std::string, radio::Station>((*iter)["name"], new radio::Station((*iter)["name"], (*iter)["uri"])));
        }
        loadFlag = true;
        dbFile.close();
    }

     void StationJson::save()
     {
        
     }

     radio::Station* StationJson::getNext(radio::Station* record)
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

     radio::Station* StationJson::getPrev(radio::Station* record)
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
}
