#pragma once

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void loadProgram(const std::string& vertShader, const std::string& fragShader);

	void enable();
	void disable();
	void addAttr(const std::string& attrName);
	GLuint getProgram();

private:
	std::string loadFile(const std::string& filename);
	GLuint compileShaders(const std::string& vertCode, const std::string& fragCode);

	GLuint shaderProgram;

	int nextAttrIndex = 0;

};

