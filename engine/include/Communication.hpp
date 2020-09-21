#pragma once

#include <string>
#include <memory>
#include <vector>

#include <zmq.hpp>

#include "Logs.hpp"

namespace comm
{
    std::vector<std::string> convertStringsToArgs(std::string message);
    /*
        convert message to vector with single args
    */

    class Engine
    {
        std::unique_ptr<zmq::context_t> context;
        std::unique_ptr<zmq::socket_t> socket;
        std::string readyMsg = "ready";
        bool debug = false;

    public:
        Engine(std::string address, bool debug);
        ~Engine();

        std::string recive();
        /*
            Waiting for message from client
            return message from client
        */

        void send(std::string message);
        /*
            send given message to client
        */
    };
} // namespace comm
