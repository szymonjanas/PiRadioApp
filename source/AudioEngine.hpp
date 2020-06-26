#pragma once

#include <gst/gst.h>
#include <string>

class AudioEngine {

    GstBus *bus;
    guint bus_watch_id;
    GstElement *pipeline;

    static gboolean bus_call(   GstBus* bus, GstMessage* msg, gpointer data);

public:

    AudioEngine(std::string url);
    ~AudioEngine();
    void play();
    void pause();
    void play();
};




















