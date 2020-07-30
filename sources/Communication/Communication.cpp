#include "Communication.hpp"

Communication::Communication() 
{
    context = std::make_unique<zmq::context_t>(1);
    socket = std::make_unique<zmq::socket_t> (*context, ZMQ_PAIR);
}

Communication::~Communication() 
{
    socket->close();
    zmq_ctx_destroy(static_cast<void *>(context.release()));
    socket.reset();
    context.reset();
}

void Communication::bind(std::string address) 
{
    socket->bind(address.c_str());
}

std::vector<std::string> Communication::getSplitArgFromReplay(std::string replay) 
{
    std::vector<std::string> args;
    short iter = -1;
    bool firstFlag = true;
    std::string str;
    for (char ch: replay){
        if (ch == ' ') firstFlag = true;
        else if (firstFlag) {
            str = "";
            args.push_back(str);
            args[++iter] += ch;
            firstFlag = false;
        } 
        else args[iter] += ch;
    }
    args.shrink_to_fit();
    return args;
}

void Communication::send(std::string message) 
{
    zmq::message_t messageData (message.size());
    memcpy (messageData.data (), static_cast<const void *>(message.c_str()), message.size());
    socket->send (messageData);
}


void Communication::run(StationsDatabaseInterface* db) 
{
    AudioEngineManager* manager = &AudioEngineManager::getManager();


    while (true){
  
        // zmq::message_t request;
        // std::string requestData;
        // socket->recv (&request);
        // requestData = std::string(static_cast<char*>(request.data()), request.size());

        std::string requestData;
        std::getline (std::cin, requestData);
        std::cout << "COMMAND: " << requestData << std::endl;

        std::vector<std::string> args = getSplitArgFromReplay(requestData);

        std::string reply = "error";

        if (args[0] == "set"){

            if (args[1] == "state"){
                manager->setState(args[2]);
                reply = manager->getState();
            } 
            
            else if (args[1] == "station") {
                manager->setStation(db->getByName(args[2]));
                reply = Station::getString(manager->getStation());
            }
        }

        else if (args[0] == "get"){

            if (args[1] == "station"){

                if (args[2] == "all"){
                    try {
                        db->load();
                        reply = db->getNamesInString();
                    } catch (std::string str){
                         replay = "error " + str;
                    }
                }
                else if (args[2] == "current")
                    reply = Station::getString(manager->getStation());
                else
                    reply = Station::getString(db->getByName(args[2]));

            } 

            else if (args[1] == "state"){
                reply = manager->getState();
            } 

            else if (args[1] == "details") {
                reply = manager->getDetails(args[2]);
            } 

        }

        std::cout << reply << std::endl;
        
    }
    delete db;
}

