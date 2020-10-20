#pragma once

#include <map>
#include <memory>
#include "json.hpp"

namespace db {

    template <typename ID, typename RECORD> 
    class Database {
        /*
            ABSTRACT CLASS
            some func must be defined in inheritance

            provided interface for plenty of Database types
            with basic functionalities
        */
    public:
        using RECORDptr = std::unique_ptr<RECORD>;
        using DATABASE =  std::map<ID, RECORDptr>;
        using RECORDS = std::vector<RECORD>;
        using RECORDSptr = std::unique_ptr<RECORDS>; 

    protected:
        DATABASE database;

    public:
        virtual ~Database();

        virtual bool isLoad() = 0;
        virtual void load() = 0;
        virtual void save() = 0;

        virtual RECORD* getNext(RECORD* record) = 0;
        virtual RECORD* getPrev(RECORD* record) = 0;

        virtual std::string toString() = 0;
        virtual nlohmann::json toJson() = 0;
        virtual nlohmann::json toFile() = 0;


        RECORD* getByID(ID id);

        void put(ID id, RECORD* record);
        void put(ID id, RECORDptr record);

        DATABASE* getDatabase();

        void remove(ID id);

        virtual RECORDSptr getValues();

    };
    
    /* 
        ## DATABASE #############################################
    */
    template<typename ID, typename RECORD>
    Database<ID, RECORD>::~Database()
    {}

    template<typename ID, typename RECORD>
    RECORD* Database<ID, RECORD>::getByID(ID id){
        if (database.find(id) != database.end())
            return database.at(id).get();
        else return nullptr;
    }

    template <typename ID, typename RECORD> 
    void Database<ID, RECORD>::put(ID id, RECORD* record){
        if (record == nullptr)
            return;
        database[id] = RECORDptr (record);
        this->save();
    }

    template <typename ID, typename RECORD> 
    void Database<ID, RECORD>::put(ID id, RECORDptr record){
        database[id] = std::move(record);
        this->save();
    }

    template<typename ID, typename RECORD>
    typename Database<ID, RECORD>::DATABASE* Database<ID, RECORD>::getDatabase(){
        return &database;
    }

    template<typename ID, typename RECORD>
    void Database<ID, RECORD>::remove(ID id){
        if (database.find(id) != database.end())
            database.erase(database.find(id));
        this->save();
    }

    template<typename ID, typename RECORD>
    typename Database<ID, RECORD>::RECORDSptr Database<ID, RECORD>::getValues(){
        RECORDSptr values (new RECORDS());
        for (auto& pair : database)
            values->push_back(*(pair.second.get()));
        return std::move(values);
    }

} // namespace db
