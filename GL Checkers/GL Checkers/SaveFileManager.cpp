#include "SaveFileManager.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <cereal\cereal.hpp>
#include <cereal\archives\binary.hpp>

namespace fs = std::tr2::sys;

template <class SavedClass>
SaveFileManager::SaveFileManager() {

}


SaveFileManager::~SaveFileManager() {

}

void SaveFileManager::loadSaves() {
	fs::directory_iterator empty;
	for (fs::directory_iterator iter(saveDir); iter != empty; iter++) {

	}
}

void SaveFileManager::loadSave(const std::string& name) {
	
}
