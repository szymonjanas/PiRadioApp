#pragma once

#include <map>
#include <string>
#include <fstream>

namespace DatabaseEngine {

	void init();
	std::map<std::string, std::string>* getDatabase();
	std::string getValue(std::string key);
	bool save(std::pair<std::string, std::string> element);

}
