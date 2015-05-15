#include "Board.h"
#include "App.h"
#include "SavedSquare.h"



Board::Board(App& app) : appRef(app), boardData(BOARD_SIZE, std::vector<Piece *>(BOARD_SIZE, nullptr)) {
	lightSquareTex = appRef.getTextureManager().getTexture("lightSquare");
	darkSquareTex = appRef.getTextureManager().getTexture("darkSquare");
	boardX = 0 - (appRef.screenWidth / 2);
	boardY = 0 - (appRef.screenHeight / 2);
}


Board::~Board() {
	for (auto row : boardData) {
		for (auto piece : row) {
			delete piece;
		}
 	}
}

void Board::save(const std::string& name) {
	std::vector<std::vector<SavedSquare>> saveData(boardData.size());
	for (int row = 0; row < boardData.size(); row++) {
		saveData[row].resize(boardData[row].size());
	}
	for (int row = 0; row < boardData.size(); row++) {
		for (int col = 0; col < boardData[row].size(); col++) {
			saveData[row][col] = pieceToSquare(boardData[row][col]);
		}
	}
	appRef.getSaveManager().save(name, saveData);
}

void Board::load(const std::string& name) {
	auto data = appRef.getSaveManager().load(name);
	for (int row = 0; row < data.size(); row++) {
		for (int col = 0; col < data[row].size(); col++) {
			SavedSquare nextSquare = data[row][col];
			if (nextSquare.hasPiece == false) {
				boardData[row][col] = nullptr;
			}
			else {
				addPiece(BoardPos{ row, col }, nextSquare.color, nextSquare.king);
			}
		}
	}
}

SavedSquare Board::pieceToSquare(Piece * piece) {
	SavedSquare returnSquare;
	if (piece == nullptr) {
		returnSquare.hasPiece = false;
		return returnSquare;
	}
	else {
		returnSquare.hasPiece = true;
		returnSquare.color = piece->getColor();
		returnSquare.king = piece->getKing();
		return returnSquare;
	}
}

Piece * Board::getPieceAt(BoardPos pos) {
	return boardData[pos.row][pos.col];
}

void Board::update() {
	mustJump = false;
	for (auto row : boardData) {
		for (auto piece : row) {
			if (piece != nullptr) {
				piece->update();
			}
		}
	}
	if (mustJump) {
		for (auto row : boardData) {
			for (auto piece : row) {
				if (piece != nullptr) {
					piece->pruneNonJumps();
				}
			}
		}
	}
}

void Board::addPiece(BoardPos pos, PieceColor color, bool king) {
	if (getPieceAt(pos) == nullptr) {
		Piece * newPiece = new Piece(pos, color, king, *this, appRef);
		boardData[pos.row][pos.col] = newPiece;
		if (color == PieceColor::WHITE) {
			numWhite++;
		}
		else {
			numBlack++;
		}
	}
}

void Board::deletePiece(BoardPos pos) {
	PieceColor color = getPieceAt(pos)->getColor();
	if (color == PieceColor::WHITE) {
		numWhite--;
	}
	else {
		numBlack--;
	}
	delete boardData[pos.row][pos.col];
	boardData[pos.row][pos.col] = nullptr;
}

bool Board::movePiece(Move move) {
	if (getPieceAt(move.oldPos)->move(move.newPos) == true) {
		boardData[move.newPos.row][move.newPos.col] = getPieceAt(move.oldPos);
		boardData[move.oldPos.row][move.oldPos.col] = nullptr;
		return true;
	}
	else {
		return false;
	}
}

void Board::render(SpriteBatch& batch) {
	renderBackground(batch);
	renderPieces(batch);
	if (selectedPiece != nullptr) {
		selectedPiece->renderSelection(batch);
	}
}

void Board::renderBackground(SpriteBatch& batch) {
	GLuint nextTex = lightSquareTex;
	for (int row = 0; row < boardData.size(); row++) {
		for (int col = 0; col < boardData[row].size(); col++) {
			float x = (col * 64) + boardX;
			float y = (row * 64) + boardY;
			batch.draw(glm::vec4(x, y, SQUARE_SIZE, SQUARE_SIZE), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), nextTex, 0, Color{ 255, 255, 255, 255 });
			if (nextTex == lightSquareTex) {
				nextTex = darkSquareTex;
			}
			else {
				nextTex = lightSquareTex;
			}
		}
		if (nextTex == lightSquareTex) {
			nextTex = darkSquareTex;
		}
		else {
			nextTex = lightSquareTex;
		}
	}
}

void Board::renderPieces(SpriteBatch& batch) {
	for (int row = 0; row < boardData.size(); row++) {
		for (int col = 0; col < boardData[row].size(); col++) {
			Piece * next = boardData[row][col];
			if (next != nullptr) {
				next->render(batch);
			}
		}
	}
}

//utility functions
BoardPos Board::mouseToBoard(glm::vec2 coords) { //converts mouse coords to board row and column coords, returns -1, -1, if point is outside of board
	BoardPos error{ -1, -1 }; //this is the error vector
	coords.x = coords.x - (appRef.screenWidth / 2);
	coords.y = coords.y - (appRef.screenHeight / 2); //convert to opengl coords
	glm::vec2 boardSpace(coords.x - boardX, -(coords.y + boardY)); //transform to board space
	BoardPos finalCoords{ glm::floor(boardSpace.y / SQUARE_SIZE), glm::floor(boardSpace.x / SQUARE_SIZE) }; //divide by square size to get row and column
	if (finalCoords.row > boardData.size() - 1) {
		return error;
	}
	else if (finalCoords.col > boardData[finalCoords.row].size() - 1){ //y is fine, check row/x
		return error;
	}
	else if (finalCoords.col < 0 || finalCoords.row < 0) { //negative coords also mean out of board
		return error;
	}
	return finalCoords; //checks have all passed
}

glm::vec2 Board::boardToScreen(BoardPos pos) { //convert board row and columns coords to sprite origin coords for drawing
	float x = (pos.col * SQUARE_SIZE) + boardX;
	float y = (pos.row * SQUARE_SIZE) + boardY;
	return glm::vec2(x, y);
}
