#include "AudioEngine.hpp"
#include <stdexcept>
#include <memory>

AudioEngine::AudioEngine(std::string url){
    int Argc = 1;
    char** Argv = new char* ();
    Argv[0] = "foo";
    gst_init (&Argc, &Argv);

    std::string playbinText = "playbin uri=" + url;
    pipeline = gst_parse_launch(playbinText.c_str(), NULL);

    if (!pipeline){
        g_printerr("Pipeline could not be created. Exiting...\n");
        throw "One element of AudioEngine could not be created!";
    }

    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    bus_watch_id = gst_bus_add_watch(bus, bus_call, loop);
}

AudioEngine::~AudioEngine(){
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
}

gboolean AudioEngine::bus_call(GstBus *bus, GstMessage *msg, gpointer data){
    GMainLoop *loop = (GMainLoop *) data;

    switch (GST_MESSAGE_TYPE (msg)) {

      case GST_MESSAGE_EOS:
        g_print ("End of stream\n");
        break;

      case GST_MESSAGE_ERROR: {
        gchar  *debug;
        GError *error;

        gst_message_parse_error (msg, &error, &debug);
        g_free (debug);

        g_printerr ("Error: %s\n", error->message);
        g_error_free (error);
        break;
      }
      default:
        break;
    }

    return TRUE;
}

void AudioEngine::play(){
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
    g_print ("Running...\n");
}

void AudioEngine::pause(){
    gst_element_set_state (pipeline, GST_STATE_PAUSED);
    g_print ("Paused,\n");
}

void AudioEngine::stop(){
    g_print ("Returned, stopping playback\n");
    gst_element_set_state (pipeline, GST_STATE_NULL);
}
