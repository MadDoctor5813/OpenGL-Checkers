#pragma once

#include <GL/glew.h>

class Sprite {

public:
	Sprite(float x, float y, float w, float h);
	~Sprite();
	void draw();

private:
	void initBuffer();

	float x, y, h, w;
	GLuint bufferId;

};

