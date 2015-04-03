#include "Piece.h"

#include "App.h"


Piece::Piece(float x, float y, PieceTypes type, App& app) : x(x), y(y), appRef(app) {
	if ((int)type > 2) { //This means the piece is a king
		king = true;
	}
	if (type == PieceTypes::WHITE || type == PieceTypes::WHITE_KING) {
		color = PieceColors::WHITE;
	}
	if (type == PieceTypes::BLACK || type == PieceTypes::BLACK_KING) {
		color = PieceColors::BLACK;
	}
	loadTexture();
}


Piece::~Piece() {
}

void Piece::handleEvent(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			y += 16;
			break;
		case SDLK_s:
			y -= 16;
			break;
		case SDLK_a:
			x -= 16;
			break;
		case SDLK_d:
			x += 16;
			break;
		}
	}
}

void Piece::update() {

}

void Piece::render() {
	appRef.getBatch().draw(glm::vec4(x, y, PIECE_SIZE, PIECE_SIZE), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture, 0, Color{ 255, 255, 255, 255 });
}

void Piece::loadTexture() {
	TextureManager& manager = appRef.getTextureManager();
	if (color == PieceColors::WHITE) {
		if (king == false) {
			texture = manager.getTexture("pieceWhite");
		}
		else {
			texture = manager.getTexture("pieceWhiteKing");
		}
	}
	else if (color == PieceColors::BLACK) {
		if (king == false) {
			texture = manager.getTexture("pieceBlack");
		}
		else {
			texture = manager.getTexture("pieceBlackKing");
		}
	}
}
