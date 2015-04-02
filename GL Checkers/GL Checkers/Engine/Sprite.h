#pragma once

#include <GL/glew.h>

class App; 

class Sprite {

public:
	Sprite(float x, float y, float w, float h, GLuint texture, App& game);
	~Sprite();

	void draw();

private:
	void initBuffer();

	GLuint texId;
	float x, y, h, w;
	GLuint bufferId;
	App& appRef;

};

