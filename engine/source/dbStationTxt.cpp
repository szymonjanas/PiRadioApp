#include "dbStationTxt.hpp"

namespace db
{
    StationsTxt::StationsTxt(std::string filePath) : filePath(filePath)
    {
    }

    bool StationsTxt::isLoad()
    {
        return loadFlag;
    }

    void StationsTxt::load()
    {
        std::fstream dbFile(filePath, std::ios::in);
        if (!dbFile.good())
            throw std::string("Cannot access file!");
        std::string record, name;
        bool nameFlag = true;
        while (std::getline(dbFile, record))
        {
            if (nameFlag)
            {
                name = record;
                nameFlag = false;
            }
            else
            {
                while (name.find('\r') != std::string::npos)
                    name.erase(name.find('\r'));
                while (name.find('\n') != std::string::npos)
                    name.erase(name.find('\n'));
                database.push_back(new RECORD<std::string, radio::Station>(name, new radio::Station(name, record)));
                nameFlag = true;
            }
        }
        loadFlag = true;
        dbFile.close();
    }

    void StationsTxt::save()
    {
        std::fstream dbFile(filePath, std::ios::out);
        if (!dbFile.good())
            throw std::string("Cannot save to file!");
        for (auto iter : database)
        {
            dbFile << iter->getValue()->getName() + "\n";
            dbFile << iter->getValue()->getUri() + "\n";
        }
        dbFile.close();
    }

    radio::Station* StationsTxt::getNext(radio::Station *record)
    {
        if (database.size() > 1) {
            if (record == nullptr) return (*(database.begin()))->getValue();
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

    radio::Station* StationsTxt::getPrev(radio::Station *record)
    {

        if (database.size() > 1) {
            if (record == nullptr) return (*(database.begin()))->getValue();
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

} // namespace db
