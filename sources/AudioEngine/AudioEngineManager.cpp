#include "AudioEngineManager.hpp"

AudioEngineManager::AudioEngineManager() 
{}

AudioEngineManager& AudioEngineManager::getManager() 
{
	static AudioEngineManager instance;
	return instance;
}

void AudioEngineManager::play()
{
	if (station != nullptr)
		if (engine.getState() == STATE::STOP)
			engine.play(station->getUri());
		else
			engine.play();
}

void AudioEngineManager::pause()
{
	if (engine.getState() == STATE::PLAY)
		engine.pause();
}

void AudioEngineManager::stop()
{
	if (engine.getState() != STATE::STOP)
		engine.stop();
}

std::string AudioEngineManager::getDetails(std::string type) 
{
	if (type == "state") {
		switch (engine.getState()){
			case STATE::PLAY: return "play";
			case STATE::PAUSE: return "pause";
			case STATE::STOP: return "stop";
		}
	} else if (type == "title") {
		return engine.getTitle();
	} else if (type == "uri") {
		return Station::getUri(station);
	} else if (type == "name") {
		return Station::getName(station);
	} else {
		return "error! wrong command!";
	}
}

void AudioEngineManager::setState(std::string state) 
{
	if (state == "play") {
		this->play();
	} else if (state == "pause") {
		this->pause();
	} else if (state == "stop") {
		this->stop();
	}
}

void AudioEngineManager::setStation(Station* station) 
{
	this->station = station;
}

Station* AudioEngineManager::getStation() 
{
	return station;
}

std::string AudioEngineManager::getState() 
{
	STATE state = engine.getState();
	switch (state)
	{
		case STATE::PLAY: return "play";
		case STATE::PAUSE: return "pause";
		case STATE::STOP: return "stop";
	}
}
