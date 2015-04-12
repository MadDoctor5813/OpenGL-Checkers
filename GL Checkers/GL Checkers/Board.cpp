#include "Board.h"
#include "App.h"


Board::Board(App& app) : appRef(app), boardData(BOARD_SIZE, std::vector<Piece *>(BOARD_SIZE, nullptr)) {
	lightSquareTex = appRef.getTextureManager().getTexture("lightSquare");
	darkSquareTex = appRef.getTextureManager().getTexture("darkSquare");
	boardX = 0 - (appRef.screenWidth / 2);
	boardY = 0 - (appRef.screenHeight / 2);
}


Board::~Board() {

}

void Board::update() {

}

void Board::handleInput(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		glm::vec2 boardCoords = mouseToBoard(glm::vec2(x, y));
		if (boardCoords != glm::vec2(-1, -1)) {
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				addPiece(glm::vec2(boardCoords.x, boardCoords.y), PieceColor::WHITE, false);
				break;
			case SDL_BUTTON_RIGHT:
				addPiece(glm::vec2(boardCoords.x, boardCoords.y), PieceColor::BLACK, false);
				break;
			}
		}
	}
}

void Board::addPiece(glm::vec2 coords, PieceColor color, bool king) {
	glm::vec2 renderCoords = boardToScreen(glm::vec2(coords.x, coords.y));
	Piece * newPiece = new Piece(renderCoords.x, renderCoords.y, color, king, *this, appRef);
	boardData[(int)coords.x][(int)coords.y] = newPiece;
}

void Board::render(SpriteBatch& batch) {
	renderBackground(batch);
	renderPieces(batch);
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
glm::vec2 Board::mouseToBoard(glm::vec2 coords) { //converts mouse coords to board row and column coords, returns -1, -1, if point is outside of board
	glm::vec2 error(-1, -1); //this is the error vector
	coords.x = coords.x - (appRef.screenWidth / 2);
	coords.y = coords.y - (appRef.screenHeight / 2); //convert to opengl coords
	glm::vec2 boardSpace(coords.x - boardX, -(coords.y + boardY)); //transform to board space
	glm::vec2 finalCoords(glm::floor(boardSpace.x / SQUARE_SIZE), glm::floor(boardSpace.y / SQUARE_SIZE)); //divide by square size to get row and column
	if (finalCoords.y > boardData.size() - 1) {
		return error;
	}
	else if (finalCoords.x > boardData[finalCoords.y].size() - 1){ //y is fine, check row/x
		return error;
	}
	else if (finalCoords.x < 0 || finalCoords.y < 0) { //negative coords also mean out of board
		return error;
	}
	return finalCoords; //checks have all passed
}

glm::vec2 Board::boardToScreen(glm::vec2 coords) { //convert board row and columns coords to sprite origin coords for drawing
	float x = (coords.x * SQUARE_SIZE) + boardX;
	float y = (coords.y * SQUARE_SIZE) + boardY;
	return glm::vec2(x, y);
}
