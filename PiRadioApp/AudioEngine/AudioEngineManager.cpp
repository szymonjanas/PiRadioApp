#include "AudioEngineManager.hpp"

static AudioEngine* engine = nullptr;

void AudioEngineManager::init()
{
	if (engine == nullptr)
		engine = new AudioEngine();
}

void AudioEngineManager::play(std::string url)
{
	if (engine == nullptr)
		engine = new AudioEngine(url);
	if (engine->getState() == STATE::STOP) {
		delete engine;
		engine = new AudioEngine(url);
	}	
	engine->play();
}

void AudioEngineManager::pause()
{
	if (engine == nullptr) return;
	engine->pause();
}

void AudioEngineManager::stop()
{
	if (engine == nullptr) return;
	engine->stop();
}

void AudioEngineManager::remove()
{
	stop();
	delete engine;
}

STATE AudioEngineManager::getState()
{
	return engine->getState();
}
