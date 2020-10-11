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
        Station();
        Station(std::string name, std::string uri);
        Station(nlohmann::json jstation);
        ~Station();

        std::string getName() const;
        std::string getUri() const;

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
