#pragma once

#include "Audio.hpp"
#include "Logs.hpp"
#include "Database.hpp"
#include "RadioStation.hpp"

namespace radio {

    class Audio
    {

        audio::EngineInterface* engine;
        radio::Station *station = nullptr;

        void play();
        void pause();
        void stop();

    public:
        Audio(audio::EngineInterface* engine);
        ~Audio();
        Audio(Audio const &) = delete;
        void operator=(Audio const &) = delete;

        void setStation(radio::Station *station);
        radio::Station *getStation();

        audio::STATE getState();

        void setState(audio::STATE state);
        void setState(std::string state);
        bool canSetState(std::string state);
        
        void setVolume(int volume);
        int getVolume();

        static std::string stateToString(audio::STATE state);
        static audio::STATE stringToState(std::string state);

        

    };

} // namespace radio
