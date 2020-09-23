#include "AudioManager.hpp"

namespace radio {

    /*
        STATICS CONVERTERS
    */

    std::string Audio::stateToString(audio::STATE state)
    {
        switch(state){
            case audio::STATE::PLAY: return "play";
            case audio::STATE::PAUSE: return "pause";
            case audio::STATE::STOP: return "stop";
            case audio::STATE::ERR: return "err";
            default: return "wrong state";
        }
    }

    audio::STATE Audio::stringToState(std::string state)
    {
        if (state == "play") return audio::STATE::PLAY;
        if (state == "pause") return audio::STATE::PAUSE;
        if (state == "stop") return audio::STATE::STOP;
        return audio::STATE::ERR;
    } 


    /*
        AUDIO MANAGER
    */

    Audio::Audio(audio::EngineInterface* engine)
    {
        this->engine = engine;
    }

    Audio::~Audio()
    {
        delete engine;
    }

    void Audio::play()
    {
        if (station != nullptr){
            if (engine->getState() == audio::STATE::STOP)
                engine->play(station->getUri());
            else
                engine->play();
            station->setPlaying(true);
        }
    }

    void Audio::pause()
    {
        if (engine->getState() == audio::STATE::PLAY)
            engine->pause();
    }

    void Audio::stop()
    {
        if (engine->getState() != audio::STATE::STOP){
            engine->stop();
            station->setPlaying(false);
        }
    }

    void Audio::setState(std::string state)
    {
        if (state == "play")
        {
            this->play();
        }
        else if (state == "pause")
        {
            this->pause();
        }
        else if (state == "stop")
        {
            this->stop();
        }
    }

    void Audio::setState(audio::STATE state)
    {
        switch(state) {
            case audio::STATE::PLAY: this->play(); break;
            case audio::STATE::PAUSE: this->pause(); break;
            case audio::STATE::STOP: this->stop(); break;
        }
    }

    bool Audio::canSetState(std::string state)
    {
        std::string currState = radio::Audio::stateToString(getState());
        if (currState == state)
            return false;
        else if (currState == "stop" && state == "play" && station != nullptr)
            return true;
        else if (currState == "play" && state == "stop")
            return true;
        return false;
    }

    void Audio::setStation(Station *station)
    {
        if (engine->getState() != audio::STATE::STOP)
            engine->stop();
        this->station = station;
    }

    Station *Audio::getStation()
    {
        return station;
    }

    audio::STATE Audio::getState()
    {
        audio::STATE state = engine->getState();
        return state;
    }

} // namespace radio
