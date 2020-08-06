#pragma once
#include <string>
#include <iostream>

namespace debug {
    void debug(std::string debug);
    void info(std::string info);
    void msg(std::string msg);
    void warn(std::string warning);
    void err(std::string err);

    void dbgMsgSet(bool status);
    bool dbgMsgGet();
}
