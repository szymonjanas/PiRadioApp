#include "ipc/IPCMessage.hpp"
#include <iostream>

namespace ipc {
    namespace message {

        IPCRecived::~IPCRecived()
        {}

        IPCRecived::IPCRecived(std::string message)
        {
            nlohmann::json jmsg = nlohmann::json::parse(message);
            try {
                route = jmsg["route"].get<std::string>();
            } catch (nlohmann::json::exception& ex) {
                route = "fake";
            }
            try {
                value = nlohmann::json::parse(jmsg["value"].get<std::string>());
            } catch (nlohmann::json::exception& ex) {
                try {
                    value = jmsg["value"];
                } catch (nlohmann::json::exception& ex) {
                    value = nlohmann::json();
                }
            }
        }

        std::string IPCRecived::getRoute() const noexcept
        {
            return route;
        }

        nlohmann::json IPCRecived::getValue() const noexcept 
        {
            return value;
        }

        IPCReply::~IPCReply()
        {}

        IPCReply::IPCReply()
        {}

        IPCReply::IPCReply(short int code, std::string message) :
            code(code), message(message)
        {}

        IPCReply::IPCReply(short int code, std::string message, nlohmann::json value) :
            code(code), message(message), value(value)
        {}

        void IPCReply::setCode(short int code)
        {
            this->code = code;
        }

        void IPCReply::setMessage(std::string message)
        {
            this->message = message;
        }

        void IPCReply::setValue(nlohmann::json value)
        {
            this->value = value;
        }

        nlohmann::json IPCReply::toJson()
        {
            nlohmann::json jData;
            jData["code"] = code;
            jData["message"] = message;
            jData["value"] = value;
            return jData;
        }

        std::string IPCReply::toString()
        {
            return this->toJson().dump();
        }

    } // namespace message
} // namespace ipc
