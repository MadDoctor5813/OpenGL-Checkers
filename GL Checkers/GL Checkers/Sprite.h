#pragma once

#include <GL/glew.h>

class Game; 

class Sprite {

public:
	Sprite(float x, float y, float w, float h, Game& game);
	~Sprite();
	void draw();

private:
	void initBuffer();

	GLuint texId;
	float x, y, h, w;
	GLuint bufferId;
	Game& gameRef;

};

