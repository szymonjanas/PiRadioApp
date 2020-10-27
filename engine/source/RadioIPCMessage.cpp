#include "RadioIPCMessage.hpp"

namespace radio {

    IPCMessage::IPCMessage(std::string message)
    {
        nlohmann::json jmsg = nlohmann::json::parse(message);
        type = toType(jmsg["type"].get<std::string>());
        applies = toApplies(jmsg["applies"].get<std::string>());
        command = jmsg["command"].get<std::string>();
        if (jmsg["station"] != nullptr)
            station = Station(jmsg["station"]);
    }

    IPCMessage::TYPE IPCMessage::toType(std::string type)
    {
        if (type == "get") return TYPE::GET;
        if (type == "post") return TYPE::POST;
        if (type == "delete") return TYPE::DELETE;
        if (type == "put") return TYPE::PUT;
        if (type == "set") return TYPE::SET;
        if (type == "error") return TYPE::ERROR;
        if (type == "switch") return TYPE::SWITCH;
    }

    IPCMessage::APPLIES IPCMessage::toApplies(std::string applies)
    {
        if (applies == "audio") return APPLIES::AUDIO;
        if (applies == "database") return APPLIES::DATABASE;
    }

}
