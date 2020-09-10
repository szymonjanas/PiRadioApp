#pragma once

#include "Station.hpp"
#include "json.hpp"
#include <vector>

namespace db {
    
    template <typename ID, typename VALUE> 
    class RECORD {   
        /*
            RECORD is using by database,
            must have same typename for id and value as database
        */
    protected:   
        ID id;
        VALUE* value;

    public:
        RECORD()
        {}
        
        RECORD(ID id, VALUE* value) : id(id), value(value)
        {}

        virtual ~RECORD(){}

        virtual ID getID();
        virtual VALUE* getValue();
        virtual void setValue(VALUE* value);
        virtual void setID(ID id);

    };

    template <typename ID, typename VALUE> 
    class Database {
        /*
            ABSTRACT CLASS
            some func must be defined in inheritance

            provided interface for plenty of Database types
            with basic functionalities
        */

    protected:
        std::vector<RECORD<ID, VALUE>*> database;

    public:
        virtual ~Database(){}

        virtual bool isLoad() = 0;
        virtual void load() = 0;
        virtual void save() = 0;

        virtual VALUE* getNext(VALUE* record) = 0;
        virtual VALUE* getPrev(VALUE* record) = 0;

        virtual std::string toString() = 0;
        virtual nlohmann::json toJson() = 0;


        RECORD<ID, VALUE>* getByID(ID id);

        void put(RECORD<ID, VALUE>* record);

        std::vector<RECORD<ID, VALUE>*>* getDatabase();

        void remove(RECORD<ID, VALUE>* record);

        virtual std::vector<VALUE*>* getValues();

    };
    

    /* 
        ## RECORD ###############################################
    */

    template <typename ID, typename VALUE> 
    ID RECORD<ID, VALUE>::getID(){
        return id;
    }

    template <typename ID, typename VALUE> 
    VALUE* RECORD<ID, VALUE>::getValue(){
        return value;
    }

    template <typename ID, typename VALUE> 
    void RECORD<ID, VALUE>::setValue(VALUE* value){
        this->value = value;
    }

    template <typename ID, typename VALUE> 
    void RECORD<ID, VALUE>::setID(ID id){
        this->id = id;
    }

    /* 
        ## DATABASE #############################################
    */

    template<typename ID, typename VALUE>
    RECORD<ID, VALUE>* Database<ID, VALUE>::getByID(ID id){
        for (auto iter : database)
        if (iter->getID() == id)
            return iter;
        return nullptr;
    }

    template <typename ID, typename VALUE> 
    void Database<ID, VALUE>::put(RECORD<ID, VALUE>* record){
        if (record == nullptr)
            return;
        if (getByID(record->getID()) != nullptr)
            getByID(record->getID())->setValue(record->getValue());
        else
            database.push_back(record);
    }

    template<typename ID, typename VALUE>
    std::vector<RECORD<ID, VALUE>*>* Database<ID, VALUE>::getDatabase(){
        return &database;
    }

    template<typename ID, typename VALUE>
    void Database<ID, VALUE>::remove(RECORD<ID, VALUE>* record){
        if (record == nullptr)
            return;
        for (auto iter = database.begin(); iter != database.end();)
            if ((*iter)->getID() == record->getID())
                database.erase(iter);
            else
                ++iter;
    }

    template<typename ID, typename VALUE>
    std::vector<VALUE*>* Database<ID, VALUE>::getValues(){
        std::vector<VALUE*>* values = new std::vector<VALUE*>();
        for (auto iter = database.begin(); iter != database.end(); ++iter){
            values->push_back((*iter)->getValue());
        }
        return values;
    }

} // namespace db
