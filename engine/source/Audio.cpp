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
                g_print("Tag list: %s \n", strTags);

                gboolean size =
                        gst_tag_list_get_tag_size(tags, GST_TAG_TITLE);
                g_print("Got title tag with size %i\n", (int)size);
                if (size)
                {
                    gchar *title;
                    gst_tag_list_get_string(tags, GST_TAG_TITLE, &title);
                    g_print("VALUE: %s \n", title);
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
    g_print("Running...\n");
    state = STATE::PLAY;
}

void Engine::pause()
{
    gst_element_set_state(pipeline, GST_STATE_PAUSED);
    g_print("Paused.\n");
    state = STATE::PAUSE;
}

void Engine::stop()
{
    g_print("Returned, stopping playback.\n");
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    state = STATE::STOP;
}


Manager::Manager()
{
}

Manager &Manager::getManager()
{
    static Manager instance;
    return instance;
}

void Manager::play()
{
    if (station != nullptr)
        if (engine.getState() == STATE::STOP)
            engine.play(station->getUri());
        else
            engine.play();
}

void Manager::pause()
{
    if (engine.getState() == STATE::PLAY)
        engine.pause();
}

void Manager::stop()
{
    if (engine.getState() != STATE::STOP)
        engine.stop();
}

std::string Manager::getDetails(std::string type)
{
    if (type == "state")
    {
        switch (engine.getState())
        {
            case STATE::PLAY:
                return "play";
            case STATE::PAUSE:
                return "pause";
            case STATE::STOP:
                return "stop";
        }
    }
    else if (type == "title")
    {
        return engine.getTitle();
    }
    else if (type == "uri")
    {
        return Station::getUri(station);
    }
    else if (type == "name")
    {
        return Station::getName(station);
    }
    else
    {
        return "error! wrong command!";
    }
}

void Manager::setState(std::string state)
{
    if (state == "play")
    {
        this->play();
    }
    else if (state == "pause")
    {
        this->pause();
    }
    else if (state == "stop")
    {
        this->stop();
    }
}

bool Manager::canSetState(std::string state)
{
    if (getState() == state)
        return false;
    else if (getState() == "stop" && state == "play" && station != nullptr)
        return true;
    else if (getState() == "play" && state == "stop")
        return true;
    return false;
}

std::string Manager::toString()
{
    std::string str;
    if (station != nullptr)
    {
        str += station->getName() + " ";
        str += engine.getTitle() + " ";
        str += station->getUri();
    }
    else
    {
        str += "unknown ";
        str += "unknown ";
        str += "unknown";
    }
    return str;
}

void Manager::setStation(Station *station)
{
    if (engine.getState() != STATE::STOP)
        engine.stop();
    this->station = station;
}

Station *Manager::getStation()
{
    return station;
}

std::string Manager::getState()
{
    STATE state = engine.getState();
    switch (state)
    {
        case STATE::PLAY:
            return "play";
        case STATE::PAUSE:
            return "pause";
        case STATE::STOP:
            return "stop";
    }
}
