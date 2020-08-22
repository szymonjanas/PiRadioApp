#pragma once

#include <gst/gst.h>
#include <string>
#include "Station.hpp"

namespace Audio
{
    enum class STATE
    {
        PLAY,
        PAUSE,
        STOP
    };

    class Engine
    {

        GstElement *pipeline;
        GstBus *bus;
        GstMessage *msg;
        guint busWatchID;
        static gboolean my_bus_callback(GstBus *bus, GstMessage *message, gpointer data);
        STATE state = STATE::STOP;

        void deletePipeline();

    public:
        Engine();
        ~Engine();
        void play(std::string url);
        void play();
        void pause();
        void stop();
        void debugMessage();
        std::string getTitle();
        void setVolume(double volume);
        STATE getState();
    };

    class Manager
    {

        Engine engine;
        Station *station = nullptr;

        Manager();

        void play();
        void pause();
        void stop();

    public:
        Manager(Manager const &) = delete;
        void operator=(Manager const &) = delete;

        static Manager &getManager();

        void setStation(Station *station);
        Station *getStation();

        std::string getState();
        std::string getDetails(std::string type);

        void setState(std::string state);
        bool canSetState(std::string state);

        std::string toString();
    };

} // namespace Audio
