#include "SaveManager.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <cereal\cereal.hpp>
#include <cereal\archives\json.hpp>
#include <cereal\types\vector.hpp>

namespace fs = std::tr2::sys;

SaveManager::SaveManager() {

}

SaveManager::~SaveManager() {

}

void SaveManager::save(const std::string& name, std::vector<std::vector<SavedSquare>> data) {
	std::ofstream file;
	std::string fullPath = saveDir + name;
	std::cout << "Saving: " << name << std::endl;
	file.open(fullPath);
	if (file) {
		std::cout << "File opened." << std::endl;
	}
	else {
		std::cout << "File open error." << std::endl;
	}
	cereal::JSONOutputArchive outputAr(file);
	outputAr(data);
	file << std::endl << "}"; //this is a hack to fix a missing brace not added by cereal
	std::cout << "Save complete." << std::endl;
	file.close();
}

std::vector<std::vector<SavedSquare>> SaveManager::load(const std::string& name) {
	std::ifstream file;
	file.open(saveDir + name);
	std::vector<std::vector<SavedSquare>> returnData;
	cereal::JSONInputArchive inputAr(file);
	inputAr(returnData);
	return returnData;
}