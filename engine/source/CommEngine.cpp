#include "Communication.hpp"

namespace comm
{
    Engine::Engine(std::string address, bool debug) : debug(debug)
    {
        context = std::make_unique<zmq::context_t>(1);
        socket = std::make_unique<zmq::socket_t>(*context, ZMQ_PAIR);
        socket->bind(address.c_str());
    }

    Engine::~Engine()
    {
        socket->close();
        zmq_ctx_destroy(static_cast<void *>(context.release()));
        socket.reset();
        context.reset();
    }

    std::vector<std::string> Engine::convertStringsToArgs(std::string message)
    {
        std::vector<std::string> args;
        short iter = -1;
        bool firstFlag = true;
        std::string str;
        for (char ch : message)
        {
            if (ch == ' ')
                firstFlag = true;
            else if (firstFlag)
            {
                str = "";
                args.push_back(str);
                args[++iter] += ch;
                firstFlag = false;
            }
            else
                args[iter] += ch;
        }
        args.shrink_to_fit();
        return args;
    }

    void Engine::send(std::string message)
    {
        if (debug)
            log::info("send: " + message);
        else
        {
            zmq::message_t messageData(message.size());
            memcpy(messageData.data(), static_cast<const void *>(message.c_str()), message.size());
            socket->send(messageData);
        }
    }

    std::string Engine::recive()
    {
        std::string requestData;
        while (requestData.size() == 0)
        {
            if (debug)
            {
                std::getline(std::cin, requestData);
                log::info("command: " + requestData);
            }
            else
            {
                zmq::message_t request;
                socket->recv(&request);
                requestData = std::string(static_cast<char *>(request.data()), request.size());
                log::info("recv: " + requestData);
            }

            if (requestData == "0")
                requestData = "";
        }
        return requestData;
    }
} // namespace communication