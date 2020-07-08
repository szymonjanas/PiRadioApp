#include "AudioEngine.hpp"

AudioEngine::AudioEngine(std::string url){
    int Argc = 1;
    char** Argv = new char* ();
    Argv[0] = (char*) "fake";
    gst_init (&Argc, &Argv);
    delete [] Argv;

    std::string playbinText = "playbin uri=" + url;
    pipeline = gst_parse_launch(playbinText.c_str(), NULL);
    if (!pipeline){
        g_printerr("Pipeline could not be created. Exiting...\n");
        throw "One element of AudioEngine could not be created!";
    }

    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
}

void AudioEngine::debugMessage(){
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_TAG);
    if (msg != NULL)
        switch (GST_MESSAGE_TYPE (msg)){
            case GST_MESSAGE_TAG:
                GstTagList *tags = NULL;
                gst_message_parse_tag(msg, &tags);
                GValue* value;
                gchar* strTags = gst_tag_list_to_string(tags);
                g_print("Tag list: %s \n", strTags);

                gboolean size =
                gst_tag_list_get_tag_size(tags, GST_TAG_TITLE);
                g_print ("Got title tag with size %i\n", (int) size);
                if (size){
                    gchar* title;
                    gst_tag_list_get_string (tags, GST_TAG_TITLE, &title);
                    g_print("VALUE: %s \n", title);
                }
        }
}

std::string AudioEngine::getTitle(){
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_TAG);
    if (msg != NULL)
        switch (GST_MESSAGE_TYPE (msg)){
            case GST_MESSAGE_TAG: {
                GstTagList *tags = NULL;
                gst_message_parse_tag(msg, &tags);
                gboolean size = gst_tag_list_get_tag_size(tags, GST_TAG_TITLE);
                if (size){
                    gchar* title;
                    gst_tag_list_get_string (tags, GST_TAG_TITLE, &title);
                    return std::string(title);
                }
            }
        }
    return "unknown";
}

void AudioEngine::setVolume(double volume){
    GstElement* pulseSink = gst_bin_get_by_name(GST_BIN(pipeline), "pulsesink1");
    g_object_set(G_OBJECT(pulseSink), "volume", (gdouble) volume, NULL);
}

STATE AudioEngine::getState()
{
    return state;
}

AudioEngine::~AudioEngine(){
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
}

void AudioEngine::play(){
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
    g_print ("Running...\n");
    state = STATE::PLAY;
}

void AudioEngine::pause(){
    gst_element_set_state (pipeline, GST_STATE_PAUSED);
    g_print ("Paused.\n");
    state = STATE::PAUSE;
}

void AudioEngine::stop(){
    g_print ("Returned, stopping playback.\n");
    gst_element_set_state (pipeline, GST_STATE_NULL);
    state = STATE::STOP;
}

gboolean
AudioEngine::my_bus_callback (GstBus * bus, GstMessage * message, gpointer data)
{
    std::cout << "HELLO!" << std::endl;
    g_print("HELLLLLLOOOOO!!!");
    //  g_print ("Got %s message\n", GST_MESSAGE_TYPE_NAME (message));
//  switch (GST_MESSAGE_TYPE (msg)) {
//    case GST_MESSAGE_TAG: {
//      GstTagList *tags = NULL;

//      gst_message_parse_tag (msg, &amp.tags);
//      g_print ("Got tags from element %s\n", GST_OBJECT_NAME (msg->src));
//      handle_tags (tags);
//      gst_tag_list_unref (tags);
//      break;
//    }
  return TRUE;
}
