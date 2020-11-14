#pragma once

#include <string>

#include <gst/gst.h>

#include "RadioStation.hpp"
#include "Logs.hpp"

namespace audio
{
    enum class STATE
    {
        PLAY,
        PAUSE,
        STOP,
        ERR
    };

    class EngineInterface 
    {

    public:
        virtual ~EngineInterface(){}
        virtual void play(std::string url) = 0;
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;
        virtual void debugMessage() = 0;
        virtual std::string getTitle() = 0;
        virtual void setVolume(int volume) = 0;
        virtual int getVolume() = 0;
        virtual STATE getState() = 0;

    };

    class EngineFake : public EngineInterface 
    {
        /*
            Fake class for developing and testing purpose
        */

        STATE state = STATE::STOP;
        int volume = 100;
    public:

        void play(std::string url) override {play();}
        void play() override {state = STATE::PLAY;}
        void pause() override {state = STATE::PAUSE;}
        void stop() override {state = STATE::STOP;}
        void debugMessage() override {}
        std::string getTitle() override {return "Title Test Text";}
        void setVolume(int volume) override {this->volume = volume;}
        STATE getState() override {return state;}
        int getVolume() override {return volume;}
    };

    class Engine : public EngineInterface
    {
        /*
            Engine class is a simple player.
            To play audio you must pass uri to source (web stream, local file, etc).
            Audio can be manipulated by: play(), pause(), stop().
            To get information about current music (in web stream): getTitle(), 
                but there is no guarantee to get title (can be unavaliable or unknown).
            Audio player is playing stream on separate thread.
        */

        GstElement *pipeline;
        GstBus *bus;
        GstMessage *msg;
        guint busWatchID;
        static gboolean my_bus_callback(GstBus *bus, GstMessage *message, gpointer data);
        STATE state = STATE::STOP;
        void deletePipeline();

    public:
        Engine();
        ~Engine();
        void play(std::string url) override;
        void play() override;
        void pause() override;
        void stop() override;
        void debugMessage() override;
        std::string getTitle() override;
        void setVolume(int volume) override;
        int getVolume() override;
        STATE getState() override;
    };

} // namespace audio
