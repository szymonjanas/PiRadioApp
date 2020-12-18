#include "Radio.hpp"

namespace radio {

    void Radio::add(std::string arg, execArgFunc func) 
    {
        ExecArgs::add(arg, (execArgsFuncPtr)(func));
    }

    Radio::Radio(int argc, char **argv)
    {
        this->all();
        std::vector<std::string> args(argv, argv + argc);
        std::vector<std::string> arguments;
        for (int iterArgs = 0; iterArgs < args.size(); ++iterArgs){
            if (args.at(iterArgs).size() > 0){
                if (args.at(iterArgs).at(0) == '-'){
                    if (iterArgs+1 < args.size()){
                        if (args.at(iterArgs+1).at(0) != '-'){
                            arguments.push_back(args[iterArgs]);
                            arguments.push_back(args[++iterArgs]);
                        } else {
                            arguments.push_back(args[iterArgs]);
                            arguments.push_back(std::string("none"));
                        }

                    } else if (iterArgs+1 == args.size()) {
                        arguments.push_back(args[iterArgs]);
                        arguments.push_back(std::string("none"));
                    } 
                }
            }
        }

        std::string argumentsStr;
        for (auto iter : arguments)
            argumentsStr += iter + " ";
        Log::info("Args: " + argumentsStr);

        for (int iter = 0; iter < arguments.size(); iter += 2)
            execute(arguments[iter], arguments[iter+1]);

        if (audioFlag) audioManager = new radio::Audio(new audio::Engine());
        else {
            audioManager = new radio::Audio(new audio::EngineFake());
            Log::warn("No audio mode!");
        }
        
        Log::warn("Database path: " + databasePath);
        database = new db::StationsJson(databasePath);
        routes = new radio::Routes(database, audioManager);
        service = new ipc::IPCService();
        Log::warn("Internal Communication Address: " + internalCommunicationAddress);
        service->connect(internalCommunicationAddress);

        manager = new radio::Manager(
                                database,
                                audioManager,
                                service,
                                routes
                            );
        
        if (!onlyFlag) {
            std::string serverArgsStr;
            for (auto& astr : serverArgs)
                serverArgsStr += astr + " ";
            Log::warn("Server starting... " + runServerCmd + " " + serverArgsStr);
            fileServer = popen(std::string(runServerCmd + " " + serverArgsStr).c_str(), "r");
            if (fileServer == NULL) {
                Log::err("Server did not start!");
            } else {
                thread_ptr = std::make_unique<std::thread>(&radio::Radio::getOutput, this, fileServer);
                thread_ptr.get()->detach();
            }
        }
    }

    Radio::~Radio()
    {
        if (fileServer != NULL){
            int status = pclose(fileServer);
            if (status == -1) Log::err("Server may be still runing!");
        }
        delete manager;
    }

    void Radio::start()
    {
        manager->start();
    }

    void Radio::getOutput(FILE *file)
    {
        char path[2048];
        while (fgets(path, sizeof(path), file) != NULL) {
            printf("%s", path);
        }
    }

    void Radio::show_help(std::string)
    {
        if (!helpPath.size()){
            Log::err("Help file path is empty!");
            throw std::string("Help file path is empty!");
        }
        std::fstream helpFile(helpPath, std::ios::in);
        if (!helpFile.good()){
            Log::err("Help file cannot be open: please check if json file exist!");
            throw std::string("Help file cannot be open: please check if json file exist!");
        }
        nlohmann::json dbJson = nlohmann::json::parse(helpFile);
        helpFile.close();

        auto stations = dbJson["help"];
        for (auto iter = stations.begin(); iter != stations.end(); ++iter)
            std::cout 
                    << "  " << (*iter)["set"].get<std::string>() << "\n" 
                    << "   " << (*iter)["short"].get<std::string>() << (((*iter)["short"].get<std::string>()).size() == 0 ? "" : "\n") 
                    << "     " << (*iter)["description"].get<std::string>() << "\n"
                    << "\n";
        exit(0);
    }

    void Radio::debug(std::string)
    {
        serverArgs.push_back("--debug");
        Log::switches::debug(true);
        debugFlag = true;
        Log::warn("Debug mode on!");
    }

    void Radio::only(std::string)
    {
        onlyFlag = true;
    }

    void Radio::set_internal_communication_address(std::string addr)
    {
        if (addr != "none")
            internalCommunicationAddress = addr;
        else throw std::string("Wrong Internal Communication Address: " + addr);
        serverArgs.push_back("-ica");
        serverArgs.push_back(addr);
    }

    void Radio::set_server_hosting_address(std::string addr)
    {
        serverArgs.push_back("-sha");
        serverArgs.push_back(addr);
    }

    void Radio::set_database(std::string path)
    {
        databasePath = path;
    }

    void Radio::colors(std::string)
    {
        serverArgs.push_back("-col");
        Log::switches::color(true);
        Log::warn("Colors mode on!");
    }

    void Radio::basic(std::string)
    {
        serverArgs.push_back("--basic");
        Log::switches::basic(true);
    }

    void Radio::no_audio(std::string)
    {
        audioFlag = false;
    }

    void Radio::set_run_server_cmd(std::string cmd)
    {
        runServerCmd = cmd;
    }

    void Radio::set_resource_path(std::string path)
    {
        serverArgs.push_back("-res");
        serverArgs.push_back(path);
    }

    void Radio::set_test_mode(std::string)
    {
        db::StationsJson::testMode = true;
    }

} // namespace radio
