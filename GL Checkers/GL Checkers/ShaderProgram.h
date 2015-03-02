#pragma once

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>

class ShaderProgram
{
public:
	ShaderProgram(std::string vertFile, std::string fragFile);
	~ShaderProgram();

	GLuint getProgram();

private:
	std::string loadFile(std::string filename);
	GLuint linkShaders();

	GLuint shaderProgram;

	std::string vertCode;
	std::string fragCode;

};

