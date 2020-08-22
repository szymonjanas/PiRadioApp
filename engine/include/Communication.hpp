#pragma once 

#include <string>
#include <memory>
#include <vector>
#include "DebugMsg.hpp"
#include <zmq.hpp>

class Communication {

    std::unique_ptr<zmq::context_t> context;
    std::unique_ptr<zmq::socket_t> socket;

    std::string readyMsg = "ready";

    bool debug = false;

public:
    Communication(bool debug, std::string address);
    ~Communication();
    std::string recive();
    void send(std::string message);
    std::vector<std::string> convertStringsToArgs(std::string);
};
