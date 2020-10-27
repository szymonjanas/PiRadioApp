#pragma once

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
            IPCReply(short int code, std::string message, nlohmann::json value);
            IPCReply(short int code, std::string message);
            virtual ~IPCReply();

            void setCode(short int code);
            void setMessage(std::string message);
            void setValue(nlohmann::json value);

            nlohmann::json toJson();
            std::string toString();

        };

    } // namespace message
} // namespace ipc
