#include "ShaderManager.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <set>

ShaderManager::ShaderManager() {
}


ShaderManager::~ShaderManager() {

}

ShaderProgram ShaderManager::getShader(const std::string& shaderName) {
	return programs.at(shaderName);
}

void ShaderManager::loadPrograms() {
	std::set<std::string> shaderNames;
	fs::directory_iterator shaderIterator(shaderDir);
	fs::directory_iterator end;
	for (; shaderIterator != end; shaderIterator++) { //Loop through all files in shader directory
		shaderNames.insert(shaderIterator->path().basename()); //add basenames of all files to set, std::set ensures uniqueness
	}
	for (auto shader : shaderNames) { //For every unique name
		std::string vertData = loadShaderData(shader + ".vert"); //Load vert and frag shaders
		std::string fragData = loadShaderData(shader + ".frag");
		ShaderProgram program;
		program.loadProgram(vertData, fragData);
		programs.insert(std::pair<std::string, ShaderProgram>(shader, program));
	}
}

std::string ShaderManager::loadShaderData(const std::string& filename) {
	std::string fullPath = shaderDir + filename;
	std::ifstream fileStream(fullPath);
	std::stringstream fileStrStream;
	fileStrStream << fileStream.rdbuf();
	return fileStrStream.str();
}

