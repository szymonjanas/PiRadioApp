#include "AudioEngine.hpp"
#include <iostream>

int main(){
    std::cout << "Hello World!";

    AudioEngine audio("https://stream.open.fm/127?type=.mp3");
    char in;
    while (true){
        std::cin >> in;
        switch (in){
            case 'P': audio.setState(AudioEngine::AudioState::PAUSE); break;
            case 'p': audio.setState(AudioEngine::AudioState::PLAY); break;
            case 's': audio.setState(AudioEngine::AudioState::STOP);
        }
    }
}















