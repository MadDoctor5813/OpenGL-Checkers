#pragma once

#include <vector>
#include <SDL.h>

class Piece;

const int BOARD_SIZE = 8; //board size in squares
const int SQUARE_SIZE = 64;

class Board {

public:
	Board();
	~Board();

	void handleInput(SDL_Event& event);
	void update();
	void render();

	void getPieceAt(int row, int col);

private:
	float x = 0;
	float y = 0;

	std::vector< std::vector <Piece *> > boardData; //Stores all pointers to all the pieces in the board, and nullptr for empty spaces;

	void populatePieces();
};

