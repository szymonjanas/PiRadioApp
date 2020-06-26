#pragma once

#include <gst/gst.h>
#include <string>

class AudioEngine {

    GstBus *bus;
    guint bus_watch_id;
    GMainLoop *loop;
    GstElement *pipeline;

    static gboolean bus_call(   GstBus* bus, GstMessage* msg, gpointer data);

public:

    enum AudioState {PLAY, PAUSE, STOP};

    AudioEngine(std::string url);
    bool setState(AudioState state);
};




















