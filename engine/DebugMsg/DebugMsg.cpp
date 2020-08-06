#include "DebugMsg.hpp"

static bool debugMsg = false;

void debug::debug(std::string debug) 
{
    if (debugMsg)
        std::cout << std::string("\033[38;5;162m") + "DEBUG: " + debug + std::string("\033[0m")  << std::endl;
}

void debug::info(std::string info) 
{
    std::cout << std::string("\033[38;5;99m") + "INFO: " + info + std::string("\033[0m")  << std::endl;
}

void debug::msg(std::string msg) 
{
    std::cout << std::string("\033[38;5;123m") + "MSG: " + msg + std::string("\033[0m")  << std::endl;
}

void debug::warn(std::string warning) 
{
    std::cout << std::string("\033[38;5;82m") + "WARN: " + warning + std::string("\033[0m")  << std::endl;
}

void debug::err(std::string err) 
{
    std::cout << std::string("\033[38;5;124m") + "ERROR: " + err + std::string("\033[0m")  << std::endl;
}

void debug::dbgMsgSet(bool status) 
{
    debugMsg = status;
}

bool debug::dbgMsgGet() 
{
    return debugMsg;
}

