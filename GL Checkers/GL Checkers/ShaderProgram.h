#pragma once

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertFile, const std::string& fragFile);
	~ShaderProgram();

	GLuint getProgram();
	void addAttr(const std::string& attrName);

private:
	std::string loadFile(const std::string& filename);
	GLuint linkShaders();

	GLuint shaderProgram;

	std::string vertCode;
	std::string fragCode;

	int nextAttrIndex = 0;

};

