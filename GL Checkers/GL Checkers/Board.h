#pragma once

#include <vector>
#include <SDL.h>

class Piece;

const int BOARD_SIZE = 8; //board size in squares

class Board {

public:
	Board();
	~Board();

	void handleInput(SDL_Event& event);
	void update();
	void render();

	void getPieceAt(int row, int col);

private:
	std::vector< std::vector <Piece *> > boardData; //Stores all pointers to all the pieces in the board, and nullptr for empty spaces;
};

