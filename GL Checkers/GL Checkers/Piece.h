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
	Piece(BoardPos pos, PieceColor color, bool king, Board& board, App& app);
	~Piece();

	void handleEvent(SDL_Event& event);
	void update();
	void render(IndexedRenderer& renderer);
	void renderSelection(IndexedRenderer& renderer);

	bool move(BoardPos newPos);
	void pruneNonJumps();

	void logInfo();

	PieceColor getColor() { return color; }
	bool getKing() { return king; }
	BoardPos getPos() { return pos; }
	void setKing(bool kingValue);

private:
	void loadTextures();

	void genMoves();
	void genMovesWhite();
	void genMovesBlack();

	std::vector<Move> moves;

	bool updateTexture = true;

	App& appRef;
	Board& boardRef;
	GLuint texture;
	GLuint selectedTexture;

	PieceColor color;
	bool king = false;

	BoardPos pos;
};

