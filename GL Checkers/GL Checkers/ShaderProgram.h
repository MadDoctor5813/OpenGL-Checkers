#pragma once

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertShader, const std::string& fragShader);
	~ShaderProgram();

	GLuint getProgram();
	void addAttr(const std::string& attrName);

private:
	std::string loadFile(const std::string& filename);
	GLuint linkShaders(const std::string& vertCode, const std::string& fragCode);

	GLuint shaderProgram;

	int nextAttrIndex = 0;

};

