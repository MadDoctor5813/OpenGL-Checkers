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
				addPiece(glm::vec2(col, row), nextSquare.color, nextSquare.king);
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

Piece * Board::getPieceAt(int row, int col) {
	return boardData[row][col];
}

void Board::update() {

}

void Board::handleInput(SDL_Event& event) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (devMode) {
			handleMouseDev(x, y, event.button.button);
		}
		else {
			handleMouse(x, y, event.button.button);
		}
	}
	else if (event.type == SDL_KEYDOWN) {
		handleKeys(event.key.keysym.sym);
	}
}

void Board::handleMouse(int x, int y, int button) {
	glm::vec2 boardCoords = mouseToBoard(glm::vec2(x, y));
	Piece * clicked = getPieceAt(boardCoords.y, boardCoords.x);
	if (clicked != nullptr) {
		switch (button) {
		case SDL_BUTTON_LEFT:
			clicked->setSelected(!clicked->getSelected());
			break;
		}
	}
}

void Board::handleMouseDev(int x, int y, int button) {
	glm::vec2 boardCoords = mouseToBoard(glm::vec2(x, y));
	if (boardCoords != glm::vec2(-1, -1)) {
		switch (button) {
		case SDL_BUTTON_LEFT:
			addPiece(glm::vec2(boardCoords.x, boardCoords.y), PieceColor::WHITE, false);
			break;
		case SDL_BUTTON_RIGHT:
			addPiece(glm::vec2(boardCoords.x, boardCoords.y), PieceColor::BLACK, false);
			break;
		}
	}
}

void Board::handleKeys(SDL_Keycode key) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	switch (key) {
	case SDLK_d:
		std::cout << "Developer mode: " << std::boolalpha << !devMode << std::endl;
		devMode = !devMode;
		break;
	case SDLK_s:
		save("default.sav");
		break;
	case SDLK_l:
		load("default.sav");
		break;
	case SDLK_DELETE:
		if (devMode) {
			glm::vec2 coords = mouseToBoard(glm::vec2(x, y));
			if (coords != glm::vec2(-1, -1)) {
				deletePiece(coords.y, coords.x);
			}
		}
	}
}

void Board::addPiece(glm::vec2 coords, PieceColor color, bool king) {
	Piece * newPiece = new Piece(coords.x, coords.y, color, king, *this, appRef);
	boardData[(int)coords.y][(int)coords.x] = newPiece;
}

void Board::deletePiece(int row, int col) {
	delete boardData[row][col];
	boardData[row][col] = nullptr;
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
