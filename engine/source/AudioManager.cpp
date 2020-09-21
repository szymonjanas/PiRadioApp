#include "AudioManager.hpp"

namespace radio {

    Audio::Audio(audio::Engine* engine)
    {
        this->engine = engine;
    }

    Audio::~Audio()
    {
        delete engine;
    }

    void Audio::play()
    {
        if(isAudio()) 
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
        if(isAudio()) 
        if (engine->getState() == audio::STATE::PLAY)
            engine->pause();
    }

    void Audio::stop()
    {
        if(isAudio()) 
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

    void Audio::setState(STATE state)
    {
        switch(state) {
            case STATE::PLAY: this->play(); break;
            case STATE::PAUSE: this->pause(); break;
            case STATE::STOP: this->stop(); break;
        }
    }

    bool Audio::canSetState(std::string state)
    {
        if (getState() == state)
            return false;
        else if (getState() == "stop" && state == "play" && station != nullptr)
            return true;
        else if (getState() == "play" && state == "stop")
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

    std::string Audio::getState()
    {
        audio::STATE state = engine->getState();
        switch (state)
        {
            case audio::STATE::PLAY:
                return "play";
            case audio::STATE::PAUSE:
                return "pause";
            case audio::STATE::STOP:
                return "stop";
        }
    }

    void Audio::setAudio(bool status)
    {
        audio = status;
    }

    bool Audio::isAudio()
    {
        return audio;
    }


} // namespace radio
