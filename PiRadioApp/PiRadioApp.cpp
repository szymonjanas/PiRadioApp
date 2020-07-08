#include <iostream>
#include "AudioEngine/AudioEngine.hpp"
#include <boost\asio.hpp>
#include <Wt/WApplication.h>
#include "WebEngine.hpp"
#include <memory>

#include "AudioEngineManager.hpp"

int main(int argc, char ** argv)
{
    AudioEngineManager::init();

    return Wt::WRun(argc, argv, 
        [](const Wt::WEnvironment& env) {
            return std::make_unique<WebEngine>(env); 
        }
    );

}
