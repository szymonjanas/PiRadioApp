#include "ipc/IPCService.hpp"

namespace ipc {

    IPCService::IPCService()
    {
        context = std::make_unique<zmq::context_t>(1);
        socket = std::make_unique<zmq::socket_t>(*context, ZMQ_PAIR);
    }

    IPCService::~IPCService()
    {
        socket->close();
        zmq_ctx_destroy(static_cast<void *>(context.release()));
        socket.reset();
        context.reset();
    }

    void IPCService::connect(std::string name)
    {
        std::string address = "ipc://" + name;
        socket->bind(address.c_str());
    }

    std::string IPCService::recive()
    {
       std::string requestData;
        while (requestData.size() == 0)
        {
            zmq::message_t request;
            socket->recv(&request);
            requestData = std::string(static_cast<char *>(request.data()), request.size());

            if (requestData == "0")
                requestData = "";
        }
        return requestData;
    }

    void IPCService::send(std::string message)
    {
        zmq::message_t messageData(message.size());
        memcpy(messageData.data(), static_cast<const void *>(message.c_str()), message.size());
        socket->send(messageData);
    }

}
