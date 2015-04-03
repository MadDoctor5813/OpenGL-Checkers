#pragma once

#include <map>
#include <string>
#include <vector>

class SaveFileManager {

public:
	SaveFileManager();
	~SaveFileManager();

	void loadSaves();

private:
	std::string saveDir = "Saves/";

	std::map <std::string, std::vector < std::vector <int> > > saves;

	void loadFile(const std::string& name);
};

