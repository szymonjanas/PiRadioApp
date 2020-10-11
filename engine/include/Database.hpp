#pragma once

#include <map>
#include <memory>

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
        typedef std::unique_ptr<RECORD> RECORDptr;
        typedef std::map<ID, RECORDptr> DATABASE; 

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

        RECORD* getByID(ID id);

        void put(ID id, RECORD* record);

        DATABASE* getDatabase();

        void remove(ID id);

        virtual std::unique_ptr<std::vector<RECORD>> getValues();

    };
    
    /* 
        ## DATABASE #############################################
    */
    template<typename ID, typename RECORD>
    RECORD* Database<ID, RECORD>::getByID(ID id){
        for (auto& iter : database)
            if (iter->getID() == id)
                return iter->get();
        return nullptr;
    }

    template <typename ID, typename RECORD> 
    void Database<ID, RECORD>::put(ID id, RECORD* record){
        if (record == nullptr)
            return;
        if (getByID(id) != nullptr)
            database->insert({id, RECORDptr (record)});
    }

    template<typename ID, typename RECORD>
    Database<ID, RECORD>::DATABASE* Database<ID, RECORD>::getDatabase(){
        return &database;
    }

    template<typename ID, typename RECORD>
    void Database<ID, RECORD>::remove(ID id){
        if (record == nullptr)
            return;
        if (database->find(id) != database->end())
            database->erase(database->find(id));
    }

    template<typename ID, typename RECORD>
    std::unique_ptr<std::vector<RECORD>> Database<ID, RECORD>::getValues(){
        std::unique_ptr<std::vector<RECORD>> values (new std::vector<RECORD>());
        for (auto pair : database)
            values->push_back(pair.second);
        return std::move(values);
    }

} // namespace db
