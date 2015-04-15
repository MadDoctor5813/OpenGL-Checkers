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
	file << fflush;
	std::cout << "Save complete." << std::endl;
	file.close();
}