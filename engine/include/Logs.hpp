#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <algorithm>

namespace log
{
    void debug(std::string message);
    /*
        message debug start with: "DEBUG: "
        color: cyan
    */

    void info(std::string message);
    /*
        message info start with: "INFO: "
        color: light blue
    */

    void msg(std::string message);
    /*
        message msg has no label
        color: default
    */

    void warn(std::string message);
    /*
        message warn start with: "WARN: "
        color: light yellow
    */

    void err(std::string message);
    /*
        message err start with "ERROR: "
        color: red
    */

    namespace switches
    {
        void console(bool status);
        bool isConsole();
        /*
            enable/disable printing message in console
        */

        void file(bool status);
        bool isFile();
        /*
            enable/disable saving message to file
        */

        void color(bool status);
        bool isColor();
        /*
            enable/disable message colors in console
            WARNING!
            Tested only on console: Ubuntu WSL, vscode wsl, ubuntu 20.
            On specific type of console can be problem with proper printing.
            For more information search: ANSI escape code Colors
        */

        void setFile(std::string path);
        bool isFilePath();
        /*
            enable saving message to file with given relative path.
            if none path is given saving to file is disabled.
        */

        void debug(bool status);
        bool isDebug();
        /*
            enable/disbable debug message
        */

        void basic(bool status);
        /*
            Disable info and debug message.
        */

    } // namespace switches

} // namespace log
