#include "Audio.hpp"

namespace audio
{
	Manager::Manager()
	{
	}

	Manager &Manager::getManager()
	{
		static Manager instance;
		return instance;
	}

	void Manager::play()
	{
		if (station != nullptr)
			if (engine.getState() == STATE::STOP)
				engine.play(station->getUri());
			else
				engine.play();
	}

	void Manager::pause()
	{
		if (engine.getState() == STATE::PLAY)
			engine.pause();
	}

	void Manager::stop()
	{
		if (engine.getState() != STATE::STOP)
			engine.stop();
	}

	std::string Manager::getDetails(std::string type)
	{
		if (type == "state")
		{
			switch (engine.getState())
			{
			case STATE::PLAY:
				return "play";
			case STATE::PAUSE:
				return "pause";
			case STATE::STOP:
				return "stop";
			}
		}
		else if (type == "title")
		{
			return engine.getTitle();
		}
		else if (type == "uri")
		{
			return Station::getUri(station);
		}
		else if (type == "name")
		{
			return Station::getName(station);
		}
		else
		{
			return "error! wrong command!";
		}
	}

	void Manager::setState(std::string state)
	{
		if (state == "play")
		{
			this->play();
		}
		else if (state == "pause")
		{
			this->pause();
		}
		else if (state == "stop")
		{
			this->stop();
		}
	}

	bool Manager::canSetState(std::string state)
	{
		if (getState() == state)
			return false;
		else if (getState() == "stop" && state == "play" && station != nullptr)
			return true;
		else if (getState() == "play" && state == "stop")
			return true;
		return false;
	}

	std::string Manager::toString()
	{
		std::string str;
		if (station != nullptr)
		{
			str += station->getName() + " ";
			str += engine.getTitle() + " ";
			str += station->getUri();
		}
		else
		{
			str += "unknown ";
			str += "unknown ";
			str += "unknown";
		}
		return str;
	}

	void Manager::setStation(Station *station)
	{
		if (engine.getState() != STATE::STOP)
			engine.stop();
		this->station = station;
	}

	Station *Manager::getStation()
	{
		return station;
	}

	std::string Manager::getState()
	{
		STATE state = engine.getState();
		switch (state)
		{
		case STATE::PLAY:
			return "play";
		case STATE::PAUSE:
			return "pause";
		case STATE::STOP:
			return "stop";
		}
	}
} // namespace Audio
