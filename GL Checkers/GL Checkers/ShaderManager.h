#pragma once

#include "ShaderProgram.h"

#include <map>
#include <filesystem>

namespace fs = std::tr2::sys;

class ShaderManager {

public:
	ShaderManager();
	~ShaderManager();

	void loadPrograms();

private:
	std::vector<std::string> getVertShaders();
	std::vector<std::string> getFragShaders();


	fs::path vertDir = "shaders/vert";
	fs::path fragDir = "shaders/frag";
	std::map<ShaderProgram, std::string> programs;
};



