#pragma once

#include "Audio.hpp"
#include "Logs.hpp"
#include "Database.hpp"
#include "Station.hpp"
#include "Communication.hpp"

namespace radio {

    class Audio
    {

        audio::Engine* engine;
        radio::Station *station = nullptr;

        void play();
        void pause();
        void stop();

    public:
        Audio(audio::Engine* engine);
        ~Audio();
        Audio(Audio const &) = delete;
        void operator=(Audio const &) = delete;

        void setStation(radio::Station *station);
        radio::Station *getStation();

        std::string getState();
        std::string getDetails(std::string type);

        void setState(std::string state);
        bool canSetState(std::string state);

        std::string toString();
    };

}
