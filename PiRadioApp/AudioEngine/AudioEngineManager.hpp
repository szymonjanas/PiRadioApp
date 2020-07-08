#pragma once

#include <string>

#include "AudioEngine.hpp"

namespace AudioEngineManager {

	void init();

	void play(std::string url);
	void pause();
	void stop();

	void remove();

	STATE getState();
}
