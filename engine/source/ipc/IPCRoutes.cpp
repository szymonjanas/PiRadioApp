#include "ipc/IPCRoutes.hpp"

namespace ipc {

    IPCRoutes::~IPCRoutes()
    {}

    void IPCRoutes::add(std::string route, MemberMethod function)
    {
        routes[route] = function;
    }

    void IPCRoutes::execute(ipc::message::IPCRecived &recive , ipc::message::IPCReply &reply)
    {  
        if (routes.find(recive.getRoute()) != routes.end()) {
            (this->* routes.at(recive.getRoute()))(recive, reply);
        }
        else {
            reply.setCode(false);
            reply.setMessage("Error! Route not found: " + recive.getRoute());
        }
    }

}
