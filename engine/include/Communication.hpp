#pragma once

#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include "DebugMsg.hpp"
#include <zmq.hpp>

namespace comm
{

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

        static std::vector<std::string> convertStringsToArgs(std::string message);
        /*
            convert message to vector with single args 
        */
    };

    class Manager
    {
        /*
            manager provides better control over the flow of messages
        */
        Engine *engine = nullptr;

        std::queue<std::string> requests;
        std::queue<std::string> replies;

        std::thread *th_req, *th_rep;
        std::mutex replay_mutex;
        std::mutex request_mutex;

        void run_request();
        void run_replay();

        std::string reply();
        /*  
            return last reply
        */

        void request(std::string request);
        /*
            push recived request
        */

    public:
        Manager() = delete;
        Manager(Manager const &) = delete;
        Manager(Manager const &&) = delete;
        void operator=(Manager const &) = delete;
        void operator=(Manager const &&) = delete;

        Manager(comm::Engine *engine);
        ~Manager();

        void start();
        /*
            run manager engine on new thread to control message flow
        */

        bool recived();
        /*
            return true if in requests is any messages, false if not
        */

        std::string recive();
        /*
            return message from queue requests
        */

        void send(std::string message);
        /*
            add message for sending queue - replies
        */
    }
} // namespace comm
