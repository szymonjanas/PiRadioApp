#pragma once

#include <gst/gst.h>
#include <string>
#include <iostream>

enum class STATE {
    PLAY,
    PAUSE,
    STOP
};

class AudioEngine {

    GstElement *pipeline;
    GstBus* bus;
    GstMessage* msg;
    guint busWatchID;
    static gboolean my_bus_callback (GstBus * bus, GstMessage * message, gpointer data);
    STATE state = STATE::STOP;

public:

    AudioEngine(std::string url);
    ~AudioEngine();
    void play();
    void pause();
    void stop();
    void debugMessage();
    std::string getTitle();
    void setVolume(double volume);
    STATE getState();
};
