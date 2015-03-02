#include "ShaderProgram.h"

#include <GL/GL.h>
#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(std::string vertFile, std::string fragFile) {
	vertCode = loadFile(vertFile);
	fragCode = loadFile(fragFile);
	shaderProgram = linkShaders();
}


ShaderProgram::~ShaderProgram() {

}

GLuint ShaderProgram::getProgram() {
	return shaderProgram;
}

std::string ShaderProgram::loadFile(std::string filename) {
	std::string fullPath = "Shaders/" + filename;
	std::ifstream fileStream(fullPath);
	std::stringstream fileStrStream;
	fileStrStream << fileStream.rdbuf();
	return fileStrStream.str();
}

GLuint ShaderProgram::linkShaders() {
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER); //make shader objects
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char * vertCodePtr = vertCode.c_str(); //Get a pointer to the std::string's c_str, for some OpenGL reason. 
	const char * fragCodePtr = fragCode.c_str(); //Same here
	glShaderSource(vertShader, 1, &vertCodePtr, NULL); //Load vert code into vert object
	glShaderSource(fragShader, 1, &fragCodePtr, NULL); //Load frag code into frag object
	//Compile vert shader
	glCompileShader(vertShader);
	//Check for errors
	GLint vertStatus;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &vertStatus);
	if (vertStatus == GL_FALSE) {
		std::cout << "Vertex shader compile error. Undefined behavior may result." << std::endl;
		GLint maxLength;
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);
		GLchar * log = new GLchar[maxLength];
		glGetShaderInfoLog(vertShader, maxLength, NULL, log);
		std::cout << log << std::endl;
		return 0;
	}
	//Compile frag shader
	glCompileShader(fragShader);
	//Check for errors
	GLint fragStatus;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fragStatus);
	if (fragStatus == GL_FALSE) {
		std::cout << "Fragment shader compile error. Undefined behavior may result." << std::endl;
		GLint maxLength;
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);
		GLchar * log = new GLchar[maxLength];
		glGetShaderInfoLog(fragShader, maxLength, NULL, log);
		std::cout << log << std::endl;
		return 0;
	}
	//Attach shaders
	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	//Link shaders
	glLinkProgram(program);
	GLint linkStatus;
	glGetProgramiv(program, GL_COMPILE_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE) {
		std::cout << "Shader link error." << std::endl;
		return 0;
	}
	//Cleanup
	glDetachShader(program, vertShader);
	glDetachShader(program, fragShader);
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	return program;
}
