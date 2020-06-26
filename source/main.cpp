#include "AudioEngine.hpp"
#include <iostream>

int main(){
    std::cout << "Hello World!" << std::endl;

    AudioEngine audio("https://stream.open.fm/127?type=.mp3");
    std::string in;
    while (true){
        std::cin >> in;
        if (in == "play") audio.play();
        if (in == "pause") audio.pause();
        if (in == "stop") audio.stop();
        if (in == "url"){
            std::string url;
            std::cin >> url;
            if (url != "exit")
                audio.setUrl(url);
        }
        if (in == "exit"){
            audio.~AudioEngine();
            exit(0);
        }
    }
}















