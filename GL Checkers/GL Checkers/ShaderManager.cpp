#include "ShaderManager.h"

#include <vector>
#include <iostream>

ShaderManager::ShaderManager() {

}


ShaderManager::~ShaderManager() {

}

std::vector<std::string> ShaderManager::getVertShaders() {
	std::vector <std::string> vertShaders;
	fs::directory_iterator end;
	for (auto vertexName = fs::directory_iterator(vertDir); vertexName != end; vertexName++) {
		std::cout << vertexName->path() << std::endl;
	}
}
