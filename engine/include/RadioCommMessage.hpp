#pragma once 

#include <string>
#include "json.hpp"

namespace radio {

    class Message 
    {
    public:
        enum class Type {
            INFO, WARN, ERR, DEBUG, REP
        };

    private:
        Type type;
        std::string message;
        nlohmann::json jValue;

        std::string typeToString(Type type);

    public:

        Message(Type&& type, std::string&& message) : type(type), message(message)
        {}

        Message& putValue(nlohmann::json value);
        nlohmann::json toJson();

    };

    std::string Message::typeToString(Type type)
    {
        std::string strType;
        switch(type)
        {
            case Type::INFO:    strType = "INFO";   break;
            case Type::WARN:    strType = "WARN";   break;
            case Type::ERR:     strType = "ERR";    break;
            case Type::DEBUG:   strType = "DEBUG";  break;
            case Type::REP:     strType = "REP";    break;
            default:            strType = "notfound"; 
        }
        return strType;
    }

    Message& Message::putValue(nlohmann::json value){
        this->jValue = value;
        return *this;
    }

    nlohmann::json Message::toJson()
    {
        nlohmann::json jdata;
        jdata["type"] = typeToString(type);
        jdata["message"] = message;
        jdata["value"] = jValue;
        return jdata;
    }

}



