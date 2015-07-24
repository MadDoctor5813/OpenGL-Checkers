#include "Piece.h"

#include <algorithm>

#include "Engine\App.h"
#include "PieceColor.h"
#include "Move.h"
#include "Engine\SpriteRenderHelper.h"

Piece::Piece(BoardPos pos, PieceColor color, bool king, Board& board, App& app) : pos(pos), color(color), king(king), boardRef(board), appRef(app) {

	loadTextures();
}


Piece::~Piece() {
}

void Piece::setKing(bool kingValue) {
	king = kingValue;
	updateTexture = true;
}

void Piece::handleEvent(SDL_Event& event) {

}

bool Piece::move(BoardPos newPos) {
	Move requested = { pos, newPos };
	for (auto move : moves) {
		if (move == requested) {
			pos = requested.newPos;
			if (move.isCapture) {
				boardRef.deletePiece(move.capTarget);
			}
			return true;
		}
	}
	return false;
}



void Piece::update() {
	if (color == PieceColor::WHITE && pos.row == boardRef.BOARD_SIZE - 1) {
		setKing(true);
	}
	else if (color == PieceColor::BLACK && pos.row == 0) {
		setKing(true);
	}
	if (updateTexture) {
		loadTextures();
		updateTexture = false;
	}
	moves.erase(moves.begin(), moves.end());
	genMoves();
}

void Piece::logInfo() {
	std::string colorStr;
	if (color == PieceColor::WHITE) {
		colorStr = "White";
	}
	else {
		colorStr = "Black";
	}
	std::cout << colorStr << " piece at Row: " << pos.row << " and Col: " << pos.col << std::endl;
	std::cout << "Moves:" << std::endl;
	for (auto move : moves) {
		std::cout << "Row: " << move.oldPos.row << " and " << "Col: " << move.oldPos.col << " to " << "Row: " << move.newPos.row << " and " << "Col: " << move.newPos.col << std::endl;
	}
}

void Piece::pruneNonJumps() {
	for (auto it = moves.begin(); it != moves.end();) {
			if (!it->isCapture) {
				it = moves.erase(it);
			}
			else {
				++it;
			}
	}
}

void Piece::render(IndexedRenderer& renderer) {
	glm::vec2 coords = boardRef.boardToScreen(BoardPos{ pos.row, pos.col });
	renderer.draw(SpriteRenderHelper::toBatch(coords.x, coords.y, boardRef.SQUARE_SIZE, boardRef.SQUARE_SIZE), 1, texture);
}

void Piece::renderSelection(IndexedRenderer& renderer) {
	glm::vec2 coords = boardRef.boardToScreen(BoardPos{ pos.row, pos.col });
	renderer.draw(SpriteRenderHelper::toBatch(coords.x, coords.y, boardRef.SQUARE_SIZE, boardRef.SQUARE_SIZE), 2, selectedTexture);
	for (auto move : moves) {
		glm::vec2 moveCoords = boardRef.boardToScreen(move.newPos);
		renderer.draw(SpriteRenderHelper::toBatch(moveCoords.x, moveCoords.y, boardRef.SQUARE_SIZE, boardRef.SQUARE_SIZE), 2, selectedTexture);
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
	if (pos.row == boardRef.BOARD_SIZE - 1) {
		return; //White is at the very top of the board, and can't move
	}
	else {
		if (pos.col != 0) { //piece can move left
			Piece * topLeft = boardRef.getPieceAt(BoardPos{ pos.row + 1, pos.col - 1 });
			if (topLeft == nullptr) {
				moves.emplace_back(pos, BoardPos{ pos.row + 1, pos.col - 1 });
			}
			else if (pos.col > 1 && pos.row < boardRef.BOARD_SIZE - 2 && topLeft->getColor() != color) { //there is room to capture and a piece to capture
				if (boardRef.getPieceAt(BoardPos{ pos.row + 2, pos.col - 2 }) == nullptr) { //and the end space is open
					moves.emplace_back(pos, BoardPos{ pos.row + 2, pos.col - 2 }, true, topLeft->getPos());
					boardRef.setMustJump(true);
				}
			}
		}
		if (pos.col != boardRef.BOARD_SIZE - 1) { //piece can move right
			Piece * topRight = boardRef.getPieceAt(BoardPos{ pos.row + 1, pos.col + 1 });
			if (topRight == nullptr) {
				moves.emplace_back(pos, BoardPos{ pos.row + 1, pos.col + 1 });
			}
			else if (pos.col < boardRef.BOARD_SIZE - 2 && pos.row < boardRef.BOARD_SIZE - 2 && topRight->getColor() != color) { //there is room to capture and a piece to capture
				if (boardRef.getPieceAt(BoardPos{ pos.row + 2, pos.col + 2 }) == nullptr) { //and the end space is open
					moves.emplace_back(pos, BoardPos{ pos.row + 2, pos.col + 2 }, true, topRight->getPos());
					boardRef.setMustJump(true);
				}
			}
		}
	}
}

void Piece::genMovesBlack() {
	if (pos.row == 0) {
		return; //Black is at the very top of the board, and can't move
	}
	else {
		if (pos.col != 0) { //piece can move left
			Piece * bottomLeft = boardRef.getPieceAt(BoardPos{ pos.row - 1, pos.col - 1 });
			if (bottomLeft == nullptr) {
				moves.emplace_back(pos, BoardPos{ pos.row - 1, pos.col - 1 });
			}
			else if (pos.col > 1 && pos.row > 1 && bottomLeft->getColor() != color) { //there is room to capture and a piece to capture
				if (boardRef.getPieceAt(BoardPos{ pos.row - 2, pos.col - 2 }) == nullptr) { //and the end space is open
					moves.emplace_back(pos, BoardPos{ pos.row - 2, pos.col - 2 }, true, bottomLeft->getPos());
					boardRef.setMustJump(true);
				}
			}
		}
		if (pos.col != boardRef.BOARD_SIZE - 1) { //piece can move right
			Piece * bottomRight = boardRef.getPieceAt(BoardPos{ pos.row - 1, pos.col + 1 });
			if (bottomRight == nullptr) {
				moves.emplace_back(pos, BoardPos{ pos.row - 1, pos.col + 1 });
			}
			else if (pos.col > 1 && pos.row > 1 && bottomRight->getColor() != color) { //there is room to capture and a piece to capture
				if (boardRef.getPieceAt(BoardPos{ pos.row - 2, pos.col + 2 }) == nullptr) { //and the end space is open
					moves.emplace_back(pos, BoardPos{ pos.row - 2, pos.col + 2 }, true, bottomRight->getPos());
					boardRef.setMustJump(true);
				}
			}
		}
	}
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
