#include "Communication.hpp"

Communication::Communication(std::string address) 
{
    this->address = address;
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

void Communication::connect() 
{
    socket->connect(address.c_str());
}

void Communication::run() 
{
    std::string name = "Anty-Radio";
    std::string url = "http://redir.atmcdn.pl/sc/o2/Eurozet/live/antyradio.livx?audio=5";

    Station station(name, url);

    AudioEngineManager* manager = &AudioEngineManager::getManager();
    manager->setStation(&station);
    // StationsDatabaseTxt db;
    // db.load("stations.txt");

        std::cout << "FLAG 1" << std::endl;
        zmq::message_t zmqreadyMsg (readyMsg.size());
        memcpy (zmqreadyMsg.data (), static_cast<const void *>(readyMsg.c_str()), readyMsg.size());
        socket->send (zmqreadyMsg);

        // zmq::pollitem_t element = {static_cast<void *>(*socket), 0, ZMQ_POLLIN, 0};
        // zmq::poll(&element, 1, TIMEOUT_ms);
        std::cout << "FLAG 2" << std::endl;
        zmq::message_t reply;
        std::string replyData;
        // if (element.revents != 0 and ZMQ_POLLIN) {
            socket->recv (&reply);
            unsigned long size = reply.size();
            replyData = std::string(static_cast<char*>(reply.data()), size);
        // }
        // else if (element.revents == 0 and ZMQ_POLLIN) {
            // socket->close();
            // socket.reset();
        // }
        std::cout << "FLAG 3" << replyData << std::endl;
        std::vector<std::string> args = getSplitArgFromReplay(replyData);
        if (args.size() >= 3)
            if (args[0] == "set"){
                if (args[1] == "state"){
                    std::cout << "FLAG 4" << std::endl;
                    manager->setState(args[2]);
                }
            }

        
    while (true){
    }
}

