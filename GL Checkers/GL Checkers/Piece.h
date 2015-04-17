#pragma once
#include <GL\glew.h>
#include <SDL.h>
#include <glm\glm.hpp>

#include "PieceColor.h"
#include "Board.h"


class App;



class Piece {

public:
	Piece(int row, int col, PieceColor color, bool king, Board& board, App& app);
	~Piece();

	void handleEvent(SDL_Event& event);
	void update();
	void render(SpriteBatch& batch);
	PieceColor getColor() { return color; }
	bool getKing() { return king; }
	void setSelected(bool value) { selected = value; }
	bool getSelected() { return selected; }

private:
	void loadTextures();

	App& appRef;
	Board& boardRef;
	GLuint texture;
	GLuint selectedTexture;

	PieceColor color;
	bool king = false;
	bool selected = false;

	int row;
	int col;
};

