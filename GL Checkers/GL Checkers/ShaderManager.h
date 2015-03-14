#pragma once

#include "ShaderProgram.h"

#include <unordered_map>
#include <filesystem>

namespace fs = std::tr2::sys;

class ShaderManager {

public:
	ShaderManager();
	~ShaderManager();

	void loadPrograms();
	ShaderProgram getShader(const std::string& shaderName);

private:
	std::string loadShaderData(const std::string& filename);

	std::unordered_map<std::string, ShaderProgram> programs;
	std::string shaderDir = "Shaders/";
};



