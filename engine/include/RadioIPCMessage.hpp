#pragma once

#include <string>
#include "Station.hpp"
#include "json.hpp"
#include "Logs.hpp"
#include <stdexcept>

namespace radio {
            
    struct IPCMessage {

        /*
            {
                "type" : "get", // or post, put, delete, set, error
                "applies" : "audio", // or database
                "command" : "all", // any, as needed 
                "station" : "{ "name" : "xyz", "uri" : "http://xyz", "index" : 12 }"
            }

        */

        enum class TYPE {
            GET, POST, PUT, DELETE, SET, ERROR, SWITCH
        };

        enum class APPLIES {
            AUDIO, DATABASE
        };

        TYPE type;
        APPLIES applies;
        std::string command;
        radio::Station station;

        IPCMessage(std::string message);
        TYPE toType(std::string type);
        APPLIES toApplies(std::string applies);
    };

}
