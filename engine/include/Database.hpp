#pragma once

#include "Station.hpp"
#include <vector>

namespace db {
    
    template <typename ID, typename VALUE> class RECORD {   

    protected:   
        ID id;
        VALUE* value;

    public:
        RECORD()
        {}
        
        RECORD(ID id, VALUE* value) : id(id), value(value)
        {}

        virtual ~RECORD(){}

        virtual ID getID(){
            return id;
        }

        virtual VALUE* getValue(){
            return value;
        }

        virtual void setValue(VALUE* value){
            this->value = value;
        }

        virtual void setID(ID id){
            this->id = id;
        }

    };

    template <typename ID, typename VALUE> class Database {

    protected:
        std::vector<RECORD<ID, VALUE>*> database;

    public:
        virtual ~Database(){}

        virtual bool isLoad() = 0;
        virtual void load() = 0;
        virtual void save() = 0;

        RECORD<ID, VALUE>* getByID(ID id){
            for (auto iter : database)
            if (iter->getID() == id)
                return iter;
            return nullptr;
        }

        void put(RECORD<ID, VALUE>* record){
            if (record == nullptr)
                return;
            if (getByID(record->getID()) != nullptr)
                getByID(record->getID())->setValue(record->getValue());
            else
                database.push_back(record);
        }

        std::vector<RECORD<ID, VALUE>*>* getDatabase(){
            return &database;
        }

        void remove(RECORD<ID, VALUE>* record){
            if (record == nullptr)
                return;
            for (auto iter = database.begin(); iter != database.end();)
                if ((*iter)->getID() == record->getID())
                    database.erase(iter);
                else
                    ++iter;
        }

        virtual std::vector<VALUE*>* getValues(){
            std::vector<VALUE*>* values = new std::vector<VALUE*>();
            for (auto iter = database.begin(); iter != database.end(); ++iter){
                values->push_back((*iter)->getValue());
            }
            return values;
        }

        virtual VALUE* getNext(VALUE* record) = 0;
        virtual VALUE* getPrev(VALUE* record) = 0;

    };

}
