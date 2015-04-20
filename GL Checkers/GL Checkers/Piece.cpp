#include "Piece.h"

#include "App.h"
#include "PieceColor.h"

Piece::Piece(int row, int col, PieceColor color, bool king, Board& board, App& app) : row(row), col(col), color(color), king(king), boardRef(board), appRef(app) {

	loadTextures();
}


Piece::~Piece() {
}

void Piece::handleEvent(SDL_Event& event) {

}

void Piece::update() {
	moves.erase(moves.begin(), moves.end());
	genMoves();
}

void Piece::render(SpriteBatch& batch) {
	glm::vec2 coords = boardRef.boardToScreen(glm::vec2(row, col));
	batch.draw(glm::vec4(coords.x, coords.y, appRef.SQUARE_SIZE, appRef.SQUARE_SIZE), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture, 0, Color{ 255, 255, 255, 255 });
}

void Piece::renderSelection(SpriteBatch& batch) {
	glm::vec2 coords = boardRef.boardToScreen(glm::vec2(row, col));
	batch.draw(glm::vec4(coords.x, coords.y, appRef.SQUARE_SIZE, appRef.SQUARE_SIZE), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), selectedTexture, 0, Color{ 255, 255, 255, 255 });
	for (auto move : moves) {
		glm::vec2 moveCoords = boardRef.boardToScreen(glm::vec2(move.newRow, move.newCol));
		batch.draw(glm::vec4(moveCoords.x, moveCoords.y, appRef.SQUARE_SIZE, appRef.SQUARE_SIZE), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), selectedTexture, 0, Color{ 255, 255, 255, 255 });
	}
}

void Piece::genMoves() {
	if (king) {
		genMovesWhite();
		genMovesBlack();
	}
	else if (color == PieceColor::WHITE) {
		genMovesWhite();
	}
	else {
		genMovesBlack();
	}
}

void Piece::genMovesWhite() {
	if (row == boardRef.BOARD_SIZE - 1) {
		return; //White is at the very top of the board, and can't move
	}
	else {
		if (col != 0) { //piece can move left
			Piece * topLeft = boardRef.getPieceAt(row + 1, col - 1);
			if (topLeft == nullptr) {
				moves.emplace_back(row, col, row + 1, col - 1);
			}
		}
	}
}

void Piece::genMovesBlack() {

}

void Piece::loadTextures() {
	TextureManager& manager = appRef.getTextureManager();
	selectedTexture = manager.getTexture("selection");
	if (color == PieceColor::WHITE) {
		if (king == false) {
			texture = manager.getTexture("pieceWhite");
		}
		else {
			texture = manager.getTexture("pieceWhiteKing");
		}
	}
	else if (color == PieceColor::BLACK) {
		if (king == false) {
			texture = manager.getTexture("pieceBlack");
		}
		else {
			texture = manager.getTexture("pieceBlackKing");
		}
	}
}
