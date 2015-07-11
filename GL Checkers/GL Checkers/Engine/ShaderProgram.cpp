#include "ShaderProgram.h"

#include <GL/GL.h>
#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram() {
	
}


ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::loadProgram(const std::string& vertShader, const std::string& fragShader) {
	shaderProgram = compileShaders(vertShader, fragShader);
}

void ShaderProgram::enable() {
	glUseProgram(shaderProgram); //Enable shader
	for (int i = 0; i < nextAttrIndex; i++) {
		glEnableVertexAttribArray(i); //Enable all relevant vertex arrays
	}
}

void ShaderProgram::disable() {
	glUseProgram(0); //Disable shader
	for (int i = 0; i < nextAttrIndex; i++) {
		glDisableVertexAttribArray(i); //Disable all relevant vertex arrays
	}
}

GLuint ShaderProgram::getProgram() {
	return shaderProgram;
}

GLuint ShaderProgram::compileShaders(const std::string& vertCode, const std::string& fragCode) {
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
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
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
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		return 0;
	}
	//Attach shaders
	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	//Link shaders
	glLinkProgram(program);
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE) {
		std::cout << "Shader link error." << std::endl;
		GLint maxLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		GLchar * log = new GLchar[maxLength];
		glGetProgramInfoLog(program, maxLength, NULL, log);
		std::cout << log << std::endl;
		glDetachShader(program, vertShader);
		glDetachShader(program, fragShader);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		glDeleteProgram(program);
		return 0;
	}

	glDetachShader(program, vertShader);
	glDetachShader(program, fragShader);
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	return program;
}

void ShaderProgram::addAttr(const std::string& attrName) {
	glBindAttribLocation(shaderProgram, nextAttrIndex, attrName.c_str());
	nextAttrIndex++;
}

