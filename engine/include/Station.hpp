#pragma once

#include <string>

namespace radio {

    class Station
    {

        std::string name = "";
        std::string uri = "";

    public:
        Station(std::string name, std::string uri);

        std::string getName();
        std::string getUri();

        void setName(std::string name);
        void setUri(std::string uri);

        std::string toString();

        static bool check(Station *station);
        static std::string getString(Station *station);
        static std::string getName(Station *station);
        static std::string getUri(Station *station);
    };

}
