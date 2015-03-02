#include "ShaderProgram.h"

#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(std::string vertFile, std::string fragFile) {

}


ShaderProgram::~ShaderProgram() {

}

std::string ShaderProgram::loadFile(std::string filename) {
	std::string fullPath = "Shaders/" + filename;
	std::ifstream fileStream(fullPath);
	std::stringstream fileStrStream;
	fileStrStream << fileStream.rdbuf();
	return fileStrStream.str();
}
