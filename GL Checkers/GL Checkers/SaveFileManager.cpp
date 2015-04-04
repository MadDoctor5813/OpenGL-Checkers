#include "SaveFileManager.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>

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
