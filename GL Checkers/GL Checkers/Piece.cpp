#include "Piece.h"

#include "App.h"
#include "PieceColor.h"

Piece::Piece(int row, int col, PieceColor color, bool king, Board& board, App& app) : row(row), col(col), color(color), king(king), boardRef(board), appRef(app) {

	loadTexture();
}


Piece::~Piece() {
}

void Piece::handleEvent(SDL_Event& event) {

}

void Piece::update() {

}

void Piece::render(SpriteBatch& batch) {
	glm::vec2 coords = boardRef.boardToScreen(glm::vec2(row, col));
	batch.draw(glm::vec4(coords.x, coords.y, appRef.SQUARE_SIZE, appRef.SQUARE_SIZE), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture, 0, Color{ 255, 255, 255, 255 });
}

void Piece::loadTexture() {
	TextureManager& manager = appRef.getTextureManager();
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
