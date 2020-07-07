#include <iostream>
#include "AudioEngine/AudioEngine.hpp"
#include <boost\asio.hpp>
#include <Wt/WApplication.h>
#include "WebEngine.hpp"
#include <memory>

int main(int argc, char ** argv)
{

    Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {return std::make_unique<WebEngine>(env); });

    std::cout << "Hello World!" << std::endl;
    std::cout << "Avaliable command: \n play \n pause \n stop \n title \n exit \n--------" << std::endl;
    AudioEngine* audio = new AudioEngine("https://stream.open.fm/127?type=.mp3");
    std::string in;
    while (true) {
        std::cin >> in;
        if (in == "play") audio->play();
        if (in == "pause") audio->pause();
        if (in == "stop") audio->stop();
        if (in == "title") std::cout << audio->getTitle() << std::endl;
        if (in == "volume") {
            double volume;
            std::cin >> volume;
            audio->setVolume(volume);
        }
        if (in == "url") {
            std::string url;
            std::cin >> url;
            if (url != "exit") {
                delete audio;
                audio = new AudioEngine(url);
            }
        }
        if (in == "exit") {
            delete audio;
            exit(0);
        }
    }
}
