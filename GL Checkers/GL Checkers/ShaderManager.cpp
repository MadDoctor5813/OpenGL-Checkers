#include "ShaderManager.h"

#include <iostream>
#include <algorithm>

ShaderManager::ShaderManager() {
}


ShaderManager::~ShaderManager() {

}

ShaderProgram ShaderManager::getShader(const std::string& shaderName) {
	return programs.at(shaderName);
}

void ShaderManager::loadPrograms() {
	auto vertShaders = getVertShaders();
	auto fragShaders = getFragShaders();
	//sort both vectors so their orders match
	std::sort(vertShaders.begin(), vertShaders.end());
	std::sort(fragShaders.begin(), fragShaders.end());
	//loop through both vectors
	for (int i = 0; i < vertShaders.size(); i++) {
		ShaderProgram program(vertShaders.at(i), fragShaders.at(i));
		programs.emplace(vertShaders.at(i), program); //add to map	
	}
}

std::vector<std::string> ShaderManager::getVertShaders() {
	std::vector <std::string> vertShaders;
	fs::directory_iterator end;
	for (auto vertexName = fs::directory_iterator(vertDir); vertexName != end; vertexName++) {
		vertShaders.push_back(vertexName->path().basename());
	}
	return vertShaders;
}

std::vector<std::string> ShaderManager::getFragShaders() {
	std::vector <std::string> fragShaders;
	fs::directory_iterator end;
	for (auto fragName = fs::directory_iterator(vertDir); fragName != end; fragName++) {
		fragShaders.push_back(fragName->path().basename());
	}
	return fragShaders;
}

