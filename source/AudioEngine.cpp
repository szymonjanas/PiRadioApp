#include "AudioEngine.hpp"

AudioEngine::AudioEngine(std::string url){
    int Argc = 1;
    char** Argv = new char* ();
    Argv[0] = "foo";
    gst_init (&Argc, &Argv);
    delete Argv[0];
    delete Argv;

    std::string playbinText = "playbin uri=" + url;
    setPipeline(playbinText);
}

AudioEngine::~AudioEngine(){
    gst_object_unref(bus);
    deletePipeline();
}

void AudioEngine::setPipeline(std::string textPipeline){
    pipeline = gst_parse_launch(textPipeline.c_str(), NULL);
    if (!pipeline){
        g_printerr("Pipeline could not be created. Exiting...\n");
        throw "One element of AudioEngine could not be created!";
    }
}

void AudioEngine::deletePipeline(){
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
}

void AudioEngine::setUrl(std::string url){
    if (pipeline)
    deletePipeline();
    std::string playbinText = "playbin uri=" + url;
    setPipeline(playbinText);
}

void AudioEngine::play(){
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
    g_print ("Running...\n");
}

void AudioEngine::pause(){
    gst_element_set_state (pipeline, GST_STATE_PAUSED);
    g_print ("Paused.\n");
}

void AudioEngine::stop(){
    g_print ("Returned, stopping playback.\n");
    gst_element_set_state (pipeline, GST_STATE_NULL);
}
