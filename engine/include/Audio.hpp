#pragma once

#include <gst/gst.h>
#include <string>
#include "Station.hpp"
#include "Logs.hpp"

namespace audio
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

} // namespace audio
