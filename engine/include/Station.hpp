#pragma once

#include <string>
#include "json.hpp"
#include "Database.hpp"

namespace radio {

    class Station
    {

        std::string name = "";
        std::string uri = "";
        bool isPlaying = false;
        std::string title = "";

    public:
        Station(std::string name, std::string uri);

        std::string getName();
        std::string getUri();

        void setName(std::string name);
        void setUri(std::string uri);
        void setPlaying(bool state);
        void setTitle(std::string title);

        std::string toString();
        nlohmann::json toJson();

        static bool check(Station *station);
        static std::string getString(Station *station);
        static std::string getName(Station *station);
        static std::string getUri(Station *station);
    };

} // namespace radio
