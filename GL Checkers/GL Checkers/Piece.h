#pragma once
#include <GL\glew.h>
#include <SDL.h>
#include <glm\glm.hpp>

class App;

const int PIECE_SIZE = 64;

class Piece {

public:
	Piece(float x, float y, App& app);
	~Piece();

	void handleEvent(SDL_Event& event);
	void update();
	void render();

private:
	App& appRef;
	GLuint texture;
	float x;
	float y;
};

