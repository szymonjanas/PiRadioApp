#pragma once

#include <string>

#include "AudioEngine.hpp"
#include "Station.hpp"

class AudioEngineManager {

	AudioEngine engine;
	Station* station = nullptr;

	AudioEngineManager();

	void play();
	void pause();
	void stop();

public: 

	AudioEngineManager (AudioEngineManager const &) = delete;
	void operator= (AudioEngineManager const &) = delete;

	static AudioEngineManager& getManager();

	void setStation(Station* station);
	Station* getStation();

	std::string getState();
	std::string getDetails(std::string type);

	void setState(std::string state);
};
