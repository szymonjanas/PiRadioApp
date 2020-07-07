#pragma once

#include <gst/gst.h>
#include <string>
#include <iostream>

class AudioEngine {

    GstElement *pipeline;
    GstBus* bus;
    GstMessage* msg;
    guint busWatchID;
    static gboolean my_bus_callback (GstBus * bus, GstMessage * message, gpointer data);

public:

    AudioEngine(std::string url);
    ~AudioEngine();
    void play();
    void pause();
    void stop();
    void debugMessage();
    std::string getTitle();
    void setVolume(double volume);
};
