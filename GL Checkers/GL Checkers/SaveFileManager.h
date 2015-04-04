#pragma once

#include <map>
#include <string>
#include <vector>
#include <bitset>

#include "Square.h"

class SaveFileManager { //Serializes and deserializes Square structs

public:
	SaveFileManager();
	~SaveFileManager();

	void loadSaves();

private:
	std::string saveDir = "Saves/";

	std::map <std::string, std::vector<Square *> >saves;
};


