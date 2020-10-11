#pragma once

#include <string>
#include <unordered_map>
#include "json.hpp"
#include "ipc/IPCMessage.hpp"

namespace ipc {


    class IPCRoutes {
    public:
        typedef void (IPCRoutes::* MemberMethod)(ipc::message::IPCRecived& , ipc::message::IPCReply&);
        
        virtual ~IPCRoutes();
        virtual void add(std::string route, MemberMethod function);
        virtual void execute(ipc::message::IPCRecived& , ipc::message::IPCReply&);
        
    private:
        std::unordered_map<std::string, MemberMethod> routes;
    };

    /*
        IPCRoutes definition
    */

    void IPCRoutes::add(std::string route, MemberMethod function)
    {
        routes[route] = function;
    }

    void IPCRoutes::execute(ipc::message::IPCRecived &recive , ipc::message::IPCReply &reply)
    {   
        if (routes.find(recive.getRoute()) != routes.end()) {
            routes[recive.getRoute()](recive, reply);
        }
        else {
            reply.setState(false);
            reply.setMessage("Error! Route not found: " + recive.getRoute());
        }
    }

}
