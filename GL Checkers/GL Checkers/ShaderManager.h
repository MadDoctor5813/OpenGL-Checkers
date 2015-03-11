#pragma once

#include "ShaderProgram.h"

#include <map>
#include <filesystem>
#include <vector>

namespace fs = std::tr2::sys;

class ShaderManager {

public:
	ShaderManager();
	~ShaderManager();

	void loadPrograms();
	ShaderProgram getShader(const std::string& shaderName);

private:
	std::vector<std::string> getVertShaders();
	std::vector<std::string> getFragShaders();


	fs::path vertDir = "shaders/vert";
	fs::path fragDir = "shaders/frag";
	std::map<std::string, ShaderProgram> programs;
};



