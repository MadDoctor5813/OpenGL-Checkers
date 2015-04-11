#pragma once

#include <vector>
#include <SDL.h>
#include <glm/glm.hpp>
#include <GL\glew.h>

#include "SpriteBatch.h"

class Piece;


class Board {

public:
	Board(App& app);
	~Board();

	void handleInput(SDL_Event& event);
	void update();
	void render(SpriteBatch& batch);

	void getPieceAt(int row, int col);

private:
	const int SQUARE_SIZE = 64;
	const int BOARD_SIZE = 8; //This really should only be used with no save files

	float boardX;
	float boardY;

	GLuint darkSquareTex;
	GLuint lightSquareTex;

	App& appRef;

	std::vector< std::vector <Piece *> > boardData; //Stores all pointers to all the pieces in the board, and nullptr for empty spaces;

	void populatePieces();
	void renderBackground(SpriteBatch& batch);

	//utility functions
	glm::vec2 screenToBoard(glm::vec2 coords) {
		glm::vec2 boardSpace = coords - glm::vec2(boardX, boardY); //convert coords into board space based on board location
		float returnX = glm::floor(boardSpace.x / SQUARE_SIZE);
		float returnY = glm::floor(boardSpace.y / SQUARE_SIZE);
		return glm::vec2(returnX, returnY);
	}
};



