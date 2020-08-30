#include "dbStationTxt.hpp"

namespace db
{
    StationsTxt::StationsTxt(std::string filePath) : filePath(filePath)
    {
    }

    bool StationsTxt::isLoad()
    {
        return (bool)database.size();
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
                database.push_back(new radio::Station(name, record));
                nameFlag = true;
            }
        }
        dbFile.close();
    }

    void StationsTxt::save()
    {
        std::fstream dbFile(filePath, std::ios::out);
        if (!dbFile.good())
            throw std::string("Cannot save to file!");
        for (auto iter : database)
        {
            dbFile << iter->getName() + "\n";
            dbFile << iter->getUri() + "\n";
        }
        dbFile.close();
    }

    radio::Station *StationsTxt::getByID(std::string name)
    {
        for (auto iter : database)
            if (iter->getName() == name)
                return iter;
        return nullptr;
    }

    void StationsTxt::put(radio::Station *station)
    {
        if (station == nullptr)
            return;
        if (getByID(station->getName()) != nullptr)
            getByID(station->getName())->setUri(station->getUri());
        else
            database.push_back(station);
        this->save();
    }

    void *StationsTxt::getDatabase()
    {
        return reinterpret_cast<void *>(&database);
    }

    void StationsTxt::remove(radio::Station *station)
    {
        if (station == nullptr)
            return;
        for (auto iter = database.begin(); iter != database.end();)
            if ((*iter)->getName() == station->getName())
                database.erase(iter);
            else
                ++iter;
        this->save();
    }

    std::string StationsTxt::getIDsInString()
    {
        std::string all = "";
        for (auto iter : database)
            all += iter->getName() + " ";
        return all;
    }

    radio::Station* StationsTxt::getNext(radio::Station *record)
    {
        if (database.size() > 1) {
            if (record == nullptr) return *(database.begin());
            for (int iter = 0; iter < database.size(); ++iter)
                if (database[iter]->getName() == record->getName())
                    if (iter+1 < database.size())
                        return database[++iter];
                    else
                        return database[0];
        }   
        else if (database.size() == 1)
            return database[0];
        else
            return nullptr;
    }

    radio::Station* StationsTxt::getPrev(radio::Station *record)
    {

        if (database.size() > 1) {
            if (record == nullptr) return *(database.begin());
            for (int iter = database.size()-1; iter >= 0 ; --iter)
                if (database[iter]->getName() == record->getName())
                    if (iter-1 >= 0)
                        return database[--iter];
                    else 
                        return database[database.size()-1];
        }
        else if (database.size() == 1)
            return database[0];
        else
            return nullptr;
    }

} // namespace db
