#pragma once

#include <string>
#include <vector>

#include "SavedSquare.h"


class SaveManager { //Serializes and deserializes Square structs

public:
	SaveManager();
	~SaveManager();

	void save(const std::string& name, std::vector<std::vector<SavedSquare>> data);
	std::vector<std::vector<SavedSquare>> load(const std::string& name);

private:
	std::string saveDir = "saves/";
};


