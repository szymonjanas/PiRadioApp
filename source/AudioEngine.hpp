#pragma once

#include <gst/gst.h>
#include <string>

class AudioEngine {

    GstElement *pipeline;

public:

    AudioEngine(std::string url);
    ~AudioEngine();
    void play();
    void pause();
    void stop();
};
