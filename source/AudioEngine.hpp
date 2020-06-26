#pragma once

#include <gst/gst.h>
#include <string>

class AudioEngine {

    GstBus *bus;
    GstElement *pipeline;

    void setPipeline(std::string);
    void deletePipeline();

public:

    AudioEngine(std::string url);
    ~AudioEngine();
    void setUrl(std::string url);
    void play();
    void pause();
    void stop();
};




















