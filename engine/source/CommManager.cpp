#include "Communication.hpp"

namespace comm
{

    Manager::Manager(comm::Engine *engine)
    {
        this->engine = engine;
    }

    Manager::~Manager()
    {
        delete engine;
    }

    void Manager::start()
    {
        th_req = new std::thread(comm::Manager::run_request, this);
        th_req->detach();
        th_rep = new std::thread(comm::Manager::run_replay, this);
        th_rep->detach();
    }

    bool Manager::recived()
    {
        std::lock_guard<std::mutex> guard(request_mutex);
        return requests.size();
    }

    std::string Manager::recive()
    {
        std::lock_guard<std::mutex> guard(request_mutex);
        if (!recived())
            return "";
        std::string out = requests.front();
        requests.pop();
        return out;
    }

    void Manager::send(std::string message)
    {
        std::lock_guard<std::mutex> guard(replay_mutex);
        replies.push(message);
    }

    std::string Manager::reply()
    {
        std::lock_guard<std::mutex> guard(replay_mutex);
        std::string message = replies.front();
        replies.pop();
        return message;
    }

    void Manager::request(std::string request)
    {
        std::lock_guard<std::mutex> guard(request_mutex);
        requests.push(request);
    }

    void Manager::run_request()
    {
        while(true){
            std::string message = engine->recive();
            requests(message);
        }
    }

    void Manager::run_replay()
    {
        while(true){
            if (replies.size()){
                engine->send(reply());
            }
        }
    }

} // namespace comm
