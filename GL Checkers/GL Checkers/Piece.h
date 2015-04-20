#pragma once
#include <GL\glew.h>
#include <SDL.h>
#include <glm\glm.hpp>
#include <vector>

#include "PieceColor.h"
#include "Move.h"
#include "Board.h"


class App;



class Piece {

public:
	Piece(int row, int col, PieceColor color, bool king, Board& board, App& app);
	~Piece();

	void handleEvent(SDL_Event& event);
	void update();
	void render(SpriteBatch& batch);
	void renderSelection(SpriteBatch& batch);
	PieceColor getColor() { return color; }
	bool getKing() { return king; }

private:
	void loadTextures();

	void genMoves();
	void genMovesWhite();
	void genMovesBlack();

	std::vector<Move> moves;

	App& appRef;
	Board& boardRef;
	GLuint texture;
	GLuint selectedTexture;

	PieceColor color;
	bool king = false;

	int row;
	int col;
};

