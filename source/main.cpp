#include "AudioEngine.hpp"
#include <iostream>

int main(){
    std::cout << "Hello World!";

    AudioEngine audio("https://stream.open.fm/127?type=.mp3");
    audio.setState(AudioEngine::AudioState::PLAY);
}















