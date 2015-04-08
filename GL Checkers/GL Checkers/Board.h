#pragma once

#include <vector>
#include <SDL.h>
#include <glm/glm.hpp>

class Piece;


class Board {

public:
	Board();
	~Board();

	void handleInput(SDL_Event& event);
	void update();
	void render();

	void getPieceAt(int row, int col);

private:
	const int SQUARE_SIZE = 64;

	float x = 0;
	float y = 0;

	std::vector< std::vector <Piece *> > boardData; //Stores all pointers to all the pieces in the board, and nullptr for empty spaces;

	void populatePieces();

	//utility functions
	glm::vec2 screenToBoard(glm::vec2 coords) {
		glm::vec2 boardSpace = coords - glm::vec2(x, y); //convert coords into board space based on board location
		float returnX = glm::floor(boardSpace.x / SQUARE_SIZE);
		float returnY = glm::floor(boardSpace.y / SQUARE_SIZE);
	}
};



