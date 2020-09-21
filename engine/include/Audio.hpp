#pragma once

#include <string>

#include <gst/gst.h>

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
        /*
            Engine class is a simple player.
            To play audio you must pass uri to source (web stream, local file, etc).
            Audio can be manipulated by: play(), pause(), stop().
            To get information about current music (in web stream): getTitle(), 
                but there is no guarantee to get title (can be unavaliable or unknown).
            Audio player is playing stream on separate thread.
        */

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
