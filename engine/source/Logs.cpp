#include "Logs.hpp"

namespace color {

    const std::string c_red = "[0;31m";
    const std::string c_red_light = "[1;31m";
    const std::string c_green = "[0;32m";
    const std::string c_green_light = "[1;32m";
    const std::string c_yellow = "[0;33m";
    const std::string c_yellow_light = "[1;33m";
    const std::string c_blue = "[0;34m";
    const std::string c_blue_light = "[1;34m";
    const std::string c_magenta = "[0;35m";
    const std::string c_magenta_light = "[1;35m";
    const std::string c_cyan = "[0;36m";
    const std::string c_cyan_light = "[1;36m";

    const std::string c_reset = "[0m";
    const std::string c_esc = "\033";

    std::string color(std::string color, std::string message)
    {
        std::string out = color::c_esc + color + message + color::c_esc + color::c_reset;
        return out;
    }
}

static bool consoleStatus = true;
static bool colorStatus = false;

static std::string filePath = "";
static bool fileStatus = false;

static bool debugStatus = true;
static bool basicView = false;

static const std::string ID = "engine: ";

namespace
{
    std::string getTime()
    {
        auto end = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::string strTime = std::ctime(&end_time);

        while (std::find(strTime.begin(), strTime.end(), '\n') != strTime.end())
            strTime.erase(std::find(strTime.begin(), strTime.end(), '\n'));

        return strTime;
    }
} // namespace

const std::string col_ID = color::color(color::c_magenta_light, ID);

namespace logSave
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

    struct Log {
        std::string logTime;
        std::string type;
        std::string type_col;
        std::string message;

        std::string toStringClr(){
            return ID + logTime + " " + message;
        }

        std::string toString(){
            return ID + logTime + " " + type + ": " + message;
        }

        std::string toStringColored(){
            if (type == "INFO")
                return col_ID + logTime + " " + color::color(type_col, type + ": ") + message;
            else 
                return col_ID + logTime + " " + color::color(type_col, type + ": " + message);
        }
    };

    void saveLog(std::string log){
        if (!debugStatus)
            return;
        if (fileStatus && filePath.size() > 0)
            append(log);
    }

    void printLog(Log &log){
        if (consoleStatus)
            if (colorStatus)
                std::cout << log.toStringColored() << std::endl;
            else
                std::cout << log.toString() << std::endl;
        saveLog(log.toString());
    }

    void printClrLog(Log &log){
        if (consoleStatus)
            std::cout << log.toStringClr() << std::endl;
        saveLog(log.toStringClr());
    }

} // namespace logSave

namespace log {

    void debug(std::string message)
    {
        if (basicView) return;
        logSave::Log log = {
            getTime(),
            "DEBUG",
            color::c_cyan_light,
            message
        };
        logSave::printLog(log);
    }

    void info(std::string message)
    {
        if (basicView) return;
        logSave::Log log = {
            getTime(),
            "INFO",
            color::c_blue_light,
            message
        };
        logSave::printLog(log);
    }

    void msg(std::string message)
    {
        logSave::Log log = {
            getTime(),
            "INFO",
            color::c_blue_light,
            message
        };
        logSave::printClrLog(log);
    }

    void warn(std::string message)
    {
        logSave::Log log = {
            getTime(),
            "WARN",
            color::c_yellow,
            message
        };
        logSave::printLog(log);
    }

    void err(std::string message)
    {
        logSave::Log log = {
            getTime(),
            "(!) ERROR",
            color::c_red,
            message
        };
        logSave::printLog(log);
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

        void basic(bool status)
        {
            basicView = status;
        }

    } // namespace switches
} // namespace log
