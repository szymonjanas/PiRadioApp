#pragma once

#include "Audio.hpp"
#include "Logs.hpp"
#include "Database.hpp"
#include "Station.hpp"
#include "Communication.hpp"

namespace radio {

    enum class STATE {
        PLAY, PAUSE, STOP
    };

    class Audio
    {

        bool audio = true;

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

        void setState(std::string state);
        void setState(STATE state);
        bool canSetState(std::string state);
        
        void setAudio(bool state);
        bool isAudio();
    };

} // namespace radio
