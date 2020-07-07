// PiRadioApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AudioEngine/AudioEngine.hpp"


int main()
{
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









// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
