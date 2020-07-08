#include "DatabaseEngine.hpp"

static std::map<std::string, std::string>* database = nullptr;

void DatabaseEngine::init()
{
	database = new std::map<std::string, std::string>();
	std::ifstream dbFile("database.txt");
	if (!dbFile.good()) return;
	std::string record, nameRecord;
	bool name = true;
	while (std::getline(dbFile, record)) {
		if (name) {
			nameRecord = record;
			name = false;
		}
		else {
			(*database)[nameRecord] = record;
			name = true;
		}
	}
	dbFile.close();
}

std::map<std::string, std::string>* DatabaseEngine::getDatabase()
{
	if (database == nullptr) return nullptr;
	return database;
}

std::string DatabaseEngine::getValue(std::string key)
{
	if (database == nullptr) return std::string();
	return (*database)[key];
}

bool DatabaseEngine::save(std::pair<std::string, std::string> element)
{
	std::fstream dbFile("database.txt", std::ios::out);
	if (!dbFile.good()) return false;
	for (auto iter = (*database).begin(); iter != (*database).end(); ++iter) {
		dbFile << iter->first;
		dbFile << iter->second;
	}
	dbFile.close();
	return true;
}
