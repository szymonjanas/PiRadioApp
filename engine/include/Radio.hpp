#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "json.hpp"
#include "ExecArgs.hpp"
#include "Logs.hpp"
#include "Audio.hpp"
#include "AudioManager.hpp"
#include "RadioManager.hpp"
#include "dbStationJson.hpp"
#include "RadioRoutes.hpp"

#include <stdio.h>
#include <thread>
#include <memory>

namespace radio {

    class Radio : public ExecArgs {

        public:
        typedef void (radio::Radio::* execArgFunc)(std::string);
        void add(std::string arg, execArgFunc func);

        private:
        std::string helpPath = "../help.json";

        bool onlyFlag = false;
        bool consoleFlag = false;
        bool audioFlag = true;
        bool debugFlag = false;

        std::string siteAddress = "";
        std::string internalCommunicationAddress = "tcp://127.0.0.1:7982";
        std::string databasePath = "database.json";
        std::string runServerCmd = "./server ";

        std::vector<std::string> serverArgs;

        radio::Manager *manager;
        radio::Audio *audioManager;
        db::StationsJson *database;
        radio::Routes *routes;
        ipc::IPCService *service;

        FILE* fileServer;
        std::unique_ptr<std::thread> thread_ptr;
        
        public:
        Radio(int argc, char **argv);
        ~Radio();
        void start();
        void getOutput(FILE *file);

        // EXEC ARGS FUNCS
        void all();
        void show_help(std::string);
        void debug(std::string);
        void only(std::string);
        void set_internal_communication_address(std::string addr);
        void set_server_hosting_address(std::string addr);
        void set_database(std::string path);
        void colors(std::string);
        void basic(std::string);
        void no_audio(std::string);
        void set_run_server_cmd(std::string cmd);
        void set_resource_path(std::string path);
    };

    void Radio::all()
    {
        this->add("--help", &Radio::show_help);
        this->add("-h", &Radio::show_help);
        this->add("--internal-communication-address", &Radio::set_internal_communication_address);
        this->add("-ica", &Radio::set_internal_communication_address);
        this->add("--server-host-address", &Radio::set_server_hosting_address);
        this->add("-sha", &Radio::set_server_hosting_address);
        this->add("--debug", &Radio::debug);
        this->add("--only", &Radio::only);
        this->add("--database", &Radio::set_database);
        this->add("-db", &Radio::set_database);
        this->add("--colors", &Radio::colors);
        this->add("-col", &Radio::colors);
        this->add("--basic", &Radio::basic);
        this->add("--no-audio", &Radio::no_audio);
        this->add("-na", &Radio::no_audio);
        this->add("--run-server-cmd", &Radio::set_run_server_cmd);
        this->add("-rsc", &Radio::set_run_server_cmd);
        this->add("--resource", &Radio::set_resource_path);
        this->add("-res", &Radio::set_resource_path);
    }

} // namespace radio
