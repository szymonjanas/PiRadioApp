#include "Logs.hpp"

using namespace log;

static const std::string c_red = "[0;31m";
static const std::string c_red_light = "[1;31m";
static const std::string c_green = "[0;32m";
static const std::string c_green_light = "[1;32m";
static const std::string c_yellow = "[0;33m";
static const std::string c_yellow_light = "[1;33m";
static const std::string c_blue = "[0;34m";
static const std::string c_blue_light = "[1;34m";
static const std::string c_magenta = "[0;35m";
static const std::string c_magenta_light = "[1;35m";
static const std::string c_cyan = "[0;36m";
static const std::string c_cyan_light = "[1;36m";

static const std::string c_reset = "[0m";
static const std::string c_esc = "\033";

static bool consoleStatus = true;
static bool colorStatus = false;

static std::string filePath = "";
static bool fileStatus = false;

static bool debugStatus = true;

static const std::string ID = "engine: ";

namespace
{
    std::string color(std::string color, std::string message)
    {
        std::string out = c_esc + color + message + c_esc + c_reset;
        return out;
    }

    void addTime(std::string &message)
    {
        auto end = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::string strTime = std::ctime(&end_time);

        while (std::find(strTime.begin(), strTime.end(), '\n') != strTime.end())
            strTime.erase(std::find(strTime.begin(), strTime.end(), '\n'));

        message = strTime + "  " + message;
    }
} // namespace

namespace
{
    void append(std::string message)
    {
        if (fileStatus && filePath.size() > 0)
        {
            std::ofstream out;
            out.open(filePath, std::ios::out | std::ios::app);
            if (out.fail() || !out.good())
            {
                fileStatus = false;
                log::err("Cannot save log to file!");
            }
            else
            {
                out << message + '\n';
                out.close();
            }
        }
    }
} // namespace

void debug(std::string message)
{
    if (!debugStatus)
        return;
    std::string str = "DEBUG: " + message;
    addTime(str);
    if (consoleStatus)
        if (colorStatus)
            std::cout << color(c_magenta_light, ID) + color(c_cyan_light, str) << std::endl;
        else
            std::cout << ID + str << std::endl;
    if (fileStatus && filePath.size() > 0)
        append(str);
}

void info(std::string message)
{
    std::string str = "INFO: " + message;
    addTime(str);
    if (consoleStatus)
        if (colorStatus)
            std::cout << color(c_magenta_light, ID) + color(c_blue_light, str) << std::endl;
        else
            std::cout << ID + str << std::endl;
    if (fileStatus && filePath.size() > 0)
        append(str);
}

void msg(std::string message)
{
    std::string str = message;
    addTime(str);
    if (consoleStatus)
        std::cout << ID + str << std::endl;
    if (fileStatus && filePath.size() > 0)
        append(str);
}

void warn(std::string message)
{
    std::string str = "WARN: " + message;
    addTime(str);
    if (consoleStatus)
        if (colorStatus)
            std::cout << color(c_magenta_light, ID) + color(c_yellow_light, str) << std::endl;
        else
            std::cout << ID + str << std::endl;
    if (fileStatus && filePath.size() > 0)
        append(str);
}

void err(std::string message)
{
    std::string str = "(!) ERROR: " + message;
    addTime(str);
    if (consoleStatus)
        if (colorStatus)
            std::cout << color(c_magenta_light, ID) + color(c_red, str) << std::endl;
        else
            std::cout << ID + str << std::endl;
    if (fileStatus && filePath.size() > 0)
        append(str);
}

namespace switches
{
    bool isConsole()
    {
        return consoleStatus;
    }
    void console(bool status)
    {
        consoleStatus = status;
    }

    bool isFile()
    {
        return filePath.size() && fileStatus;
    }
    void file(bool status)
    {
        fileStatus = status;
    }

    bool isColor()
    {
        return colorStatus;
    }
    void color(bool status)
    {
        colorStatus = status;
    }

    bool isFilePath()
    {
        return filePath.size();
    }
    void setFile(std::string path)
    {
        filePath = path;
        fileStatus = true;
    }

    bool isDebug()
    {
        return debugStatus;
    }
    void debug(bool status)
    {
        debugStatus = status;
    }

} // namespace switches
