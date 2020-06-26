#include "AudioEngine.hpp"
#include <iostream>

int main(){
    std::cout << "Hello World!";

    AudioEngine audio("https://stream.open.fm/127?type=.mp3");
    char in;
    while (true){
        std::cin >> in;
        switch (in){
            case 'P': audio.pause(); break;
            case 'p': audio.play(); break;
            case 's': audio.stop();
        }
    }
}















