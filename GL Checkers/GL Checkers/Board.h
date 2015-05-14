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
#include "Move.h"

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
	void addPiece(BoardPos pos, PieceColor color, bool king);
	void movePiece(Move move);

	BoardPos mouseToBoard(glm::vec2 coords);
	glm::vec2 boardToScreen(BoardPos pos);

	bool getDevMode() { return devMode; }
	void setDevMode(bool mode) { devMode = mode; }

	Piece * getSelected() { return selectedPiece; }
	void setSelected(Piece * selected) { selectedPiece = selected; }

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

	SavedSquare pieceToSquare(Piece * piece);

	void renderBackground(SpriteBatch& batch);
	void renderPieces(SpriteBatch& batch);

};



