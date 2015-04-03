#pragma once
#include <GL\glew.h>
#include <SDL.h>
#include <glm\glm.hpp>

class App;

enum PieceTypes { //Should only be used on instantiation
	NONE = 0,
	WHITE = 1,
	BLACK = 2,
	WHITE_KING = 3,
	BLACK_KING = 4
};

enum PieceColors {
	WHITE,
	BLACK
};

const int PIECE_SIZE = 64;

class Piece {

public:
	Piece(float x, float y, PieceTypes type, App& app);
	~Piece();

	void handleEvent(SDL_Event& event);
	void update();
	void render();

private:
	App& appRef;
	GLuint texture;

	PieceColors color;
	bool king = false;

	float x;
	float y;
};

