#pragma once 

#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include "AudioEngineManager.hpp"
#include "StationsDatabaseTxt.hpp"
#include "Station.hpp"

#include <zmq.hpp>

class Communication {

    std::unique_ptr<zmq::context_t> context;
    std::unique_ptr<zmq::socket_t> socket;

    std::string readyMsg = "ready";
    std::vector<std::string> getSplitArgFromReplay(std::string);

    void send(std::string message);

public:
    Communication();
    ~Communication();
    void bind(std::string address);
    void run(StationsDatabaseInterface* db);
};
