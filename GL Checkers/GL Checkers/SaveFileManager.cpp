#include "SaveFileManager.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace fs = std::tr2::sys;

SaveFileManager::SaveFileManager() {

}


SaveFileManager::~SaveFileManager() {

}

void SaveFileManager::loadSaves() {
	fs::directory_iterator empty;
	for (fs::directory_iterator iter(saveDir); iter != empty; iter++) {
		loadFile(iter->path().basename());
	}
}

void SaveFileManager::loadFile(const std::string& name) {
	std::vector < std::vector <int> > data;
	std::ifstream file;
	file.open(saveDir + name + ".sav");
	std::string lineStr;
	int line = 0;
	while (!file.eof()) {
		data.push_back(std::vector<int>());
		std::getline(file, lineStr);
		std::stringstream lineStream(lineStr);
		std::cout << lineStream.str() << std::endl;
		for (int i = 0; i < lineStream.str().length(); i++) {
			int num;
			lineStream >> num;
			data[line].push_back(num);
		}
		line++;
	}
	saves.emplace(name, data);
}


