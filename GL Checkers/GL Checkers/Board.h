#pragma once

#include <vector>
#include <SDL.h>
#include <glm/glm.hpp>
#include <GL\glew.h>
#include <iostream>

#include "SpriteBatch.h"
#include "PieceColor.h"
#include "SavedSquare.h"
#include "BoardPos.h"

class Piece;


class Board {

public:
	Board(App& app);
	~Board();

	void handleInput(SDL_Event& event);
	void update();
	void render(SpriteBatch& batch);

	void load(const std::string& name);
	void save(const std::string& name);

	Piece * getPieceAt(BoardPos pos);
	void deletePiece(BoardPos pos);

	BoardPos mouseToBoard(glm::vec2 coords);
	glm::vec2 boardToScreen(BoardPos pos);

	const int BOARD_SIZE = 8; 
private:
	const int SQUARE_SIZE = 64;

	float boardX;
	float boardY;

	bool devMode = false;

	GLuint darkSquareTex;
	GLuint lightSquareTex;

	Piece * selectedPiece = nullptr;

	App& appRef;

	std::vector< std::vector <Piece *> > boardData; //Stores all pointers to all the pieces in the board, and nullptr for empty spaces;

	void handleMouse(int x, int y, int button);
	void handleMouseDev(int x, int y, int button);
	void handleKeys(SDL_Keycode key);

	void selectPiece(Piece * piece);
	void deselectPiece(Piece * piece);

	SavedSquare pieceToSquare(Piece * piece);
	void addPiece(BoardPos pos, PieceColor color, bool king);

	void renderBackground(SpriteBatch& batch);
	void renderPieces(SpriteBatch& batch);

};



