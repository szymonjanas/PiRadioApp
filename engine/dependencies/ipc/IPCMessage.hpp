St#pragma once

#include <string>
#include "json.hpp"

namespace ipc {
    namespace message {
        class IPCRecived {

            std::string route;
            nlohmann::json value;

        public:
            IPCRecived(std::string message);
            virtual ~IPCRecived();
            std::string getRoute() const noexcept;
            nlohmann::json getValue() const noexcept;
        };

        class IPCReply {
            short int code; 
            std::string message;
            nlohmann::json value;

            public:
            IPCReply();
            IPCReply(short int state, std::string message, nlohmann::json value);
            IPCReply(short int state, std::string message);
            virtual ~IPCReply();

            void setState(short int state);
            void setMessage(std::string message);
            void setValue(nlohmann::json value);

            nlohmann::json toJson();
            std::string toString();
        };


        
        // ANCHOR IPCRecived
        
        IPCRecived::IPCRecived(std::string message)
        {
            nlohmann::json jmsg = nlohmann::json::parse(message);
            try {
                route = jmsg["route"].get<std::string>();
            } catch (nlohmann::json::exception& ex) {
                route = "fake";
            }
            try {
                value = jmsg["value"];
            } catch (nlohmann::json::exception& ex) {
                value = nlohmann::json();
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


        // ANCHOR IPCReply

        IPCReply::IPCReply()
        {}

        IPCReply::IPCReply(short int state, std::string message) :
            state(state), message(message)
        {}

        IPCReply::IPCReply(short int state, std::string message, nlohmann::json value) :
            state(state), message(message), value(value)
        {}

        void IPCReply::setState(short int state)
        {
            this->state = state;
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
            jData["state"] = state;
            jData["message"] = message;
            jData["value"] = value;
            return jData;
        }

        std::string IPCReply::toString()
        {
            return this->toJson().dump();
        }

    }
}
