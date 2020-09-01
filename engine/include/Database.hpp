#pragma once

#include "Station.hpp"

namespace db {
    template <typename RECORD, typename ID> class Database {
    public:
        virtual ~Database(){}

        virtual bool isLoad() = 0;
        virtual void load() = 0;
        virtual void save() = 0;

        virtual RECORD* getByID(ID name) = 0;
        virtual void put(RECORD* record) = 0;
        virtual void* getDatabase() = 0;
        virtual void remove(RECORD* record) = 0;
        virtual std::string getIDsInString() = 0;

        virtual RECORD* getNext(RECORD* record) = 0;
        virtual RECORD* getPrev(RECORD* record) = 0;
    };

}
