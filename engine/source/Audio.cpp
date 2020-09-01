#include "Audio.hpp"

using namespace audio;

Engine::Engine()
{
    int Argc = 1;
    char **Argv = new char *();
    Argv[0] = (char *)"fake";
    gst_init(&Argc, &Argv);
    delete Argv;
}

void Engine::debugMessage()
{
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_TAG);
    if (msg != NULL)
        switch (GST_MESSAGE_TYPE(msg))
        {
            case GST_MESSAGE_TAG:
                GstTagList *tags = NULL;
                gst_message_parse_tag(msg, &tags);
                GValue *value;
                gchar *strTags = gst_tag_list_to_string(tags);
                log::info("Tag list: " + std::string(strTags));

                gboolean size =
                        gst_tag_list_get_tag_size(tags, GST_TAG_TITLE);

                if (size)
                {
                    gchar *title;
                    gst_tag_list_get_string(tags, GST_TAG_TITLE, &title);
                    log::info("VALUE: " + std::string(title));
                }
        }
}

std::string Engine::getTitle()
{
    if (state == STATE::STOP)
        return "unknown";
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_TAG);
    if (msg != NULL)
        if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_TAG)
        {
            GstTagList *tags = NULL;
            gst_message_parse_tag(msg, &tags);
            gboolean size = gst_tag_list_get_tag_size(tags, GST_TAG_TITLE);
            if (size)
            {
                gchar *title;
                gst_tag_list_get_string(tags, GST_TAG_TITLE, &title);
                return std::string(title);
            }
        }
    return "unknown";
}

void Engine::setVolume(double volume)
{
    GstElement *pulseSink = gst_bin_get_by_name(GST_BIN(pipeline), "pulsesink1");
    g_object_set(G_OBJECT(pulseSink), "volume", (gdouble)volume, NULL);
}

STATE Engine::getState()
{
    return state;
}

Engine::~Engine()
{
    if (state != STATE::STOP)
    {
        stop();
    }
}

void Engine::play(std::string url)
{
    if (state != STATE::STOP)
    {
        stop();
    }
    std::string playbinText = "playbin uri=" + url;
    pipeline = gst_parse_launch(playbinText.c_str(), NULL);
    if (!pipeline)
    {
        g_printerr("Pipeline could not be created. Exiting...\n");
        throw "One element of Engine could not be created!";
    }

    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));

    play();
}

void Engine::play()
{
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    log::warn("Running...");
    state = STATE::PLAY;
}

void Engine::pause()
{
    gst_element_set_state(pipeline, GST_STATE_PAUSED);
    log::warn("Paused.");
    state = STATE::PAUSE;
}

void Engine::stop()
{
    log::warn("Returned, stopping playback.");
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    state = STATE::STOP;
}
