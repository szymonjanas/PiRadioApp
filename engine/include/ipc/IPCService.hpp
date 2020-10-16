#pragma once

#include <string>
#include <memory>
#include "zmq.hpp"

namespace ipc {

    class IPCService {

        std::unique_ptr<zmq::context_t> context;
        std::unique_ptr<zmq::socket_t> socket;

        public:
        IPCService();
        ~IPCService();

        void connect(std::string address);

        std::string recive();
        void send(std::string message);

        IPCService(const IPCService&) = delete;
        IPCService(IPCService&&) = delete;
        IPCService& operator=(const IPCService&) = delete;

    };

} // namespace ipc
