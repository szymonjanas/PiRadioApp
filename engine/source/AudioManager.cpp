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
        if (station != nullptr)
            if (engine->getState() == audio::STATE::STOP)
                engine->play(station->getUri());
            else
                engine->play();
    }

    void Audio::pause()
    {
        if (engine->getState() == audio::STATE::PLAY)
            engine->pause();
    }

    void Audio::stop()
    {
        if (engine->getState() != audio::STATE::STOP)
            engine->stop();
    }

    std::string Audio::getDetails(std::string type)
    {
        if (type == "state")
        {
            switch (engine->getState())
            {
                case audio::STATE::PLAY:
                    return "play";
                case audio::STATE::PAUSE:
                    return "pause";
                case audio::STATE::STOP:
                    return "stop";
            }
        }
        else if (type == "title")
        {
            return engine->getTitle();
        }
        else if (type == "uri")
        {
            return Station::getUri(station);
        }
        else if (type == "name")
        {
            return Station::getName(station);
        }
        else
        {
            return "error! wrong command!";
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

    std::string Audio::toString()
    {
        std::string str;
        if (station != nullptr)
        {
            str += station->getName() + " ";
            str += engine->getTitle() + " ";
            str += station->getUri();
        }
        else
        {
            str += "unknown ";
            str += "unknown ";
            str += "unknown";
        }
        return str;
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

}
