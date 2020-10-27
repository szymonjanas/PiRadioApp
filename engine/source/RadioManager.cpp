#include "RadioManager.hpp"

namespace radio {

    Manager::Manager(db::Database<std::string, radio::Station> *database,
            radio::Audio *audio,
            ipc::IPCService *service,
            ipc::IPCRoutes *routes) :
        database(database), audio(audio), service(service), routes(routes)
    {}

    Manager::~Manager()
    {
        delete audio;
        delete database;
        delete service;
        delete routes;
    }

    void Manager::setDatabase(db::Database<std::string, radio::Station> *database)
    {
        this->database = database;
    }

    void Manager::setAudio(radio::Audio *audioEngineManager)
    {
        this->audio = audioEngineManager;
    }

    void Manager::setService(ipc::IPCService *service)
    {
        this->service = service;
    }

    void Manager::setRoutes(ipc::IPCRoutes *routes)
    {
        this->routes = routes;
    }

    void Manager::start()
    {
        Log::info("Starting...");
        while (true)
        {
            std::string request = service->recive(); 
            Log::debug("REQUEST: " + request); 
            ipc::message::IPCRecived recived (request);
            ipc::message::IPCReply reply;
            routes->execute(recived, reply);
            service->send(reply.toString());
        }
    }

} // namespace radio
