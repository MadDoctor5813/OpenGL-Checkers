#include "PlayState.h"
#include "Piece.h"
#include "HumanPlayer.h"


PlayState::PlayState(App& app) : appRef(app){

}


PlayState::~PlayState() {

}

void PlayState::enter() {
	board = new Board(appRef);
	board->load("default.sav");
}

void PlayState::exit() {
	delete board;
}

void PlayState::update() {
	if (updateNeeded) {
		board->update();
		if (board->getNumBlack() == 0) { //White has won
			std::cout << "WHITE HAS WON" << std::endl;
			board->load("default.sav");
		}
		else if (board->getNumWhite() == 0) { //Black has won
			std::cout << "BLACK HAS WON" << std::endl;
			board->load("default.sav");
		}
		updateNeeded = false;
	}
}

void PlayState::addPlayer(PieceColor color, PlayerType type) {
	switch (type) {
	case HUMAN:
		HumanPlayer * player = new HumanPlayer(*this, color);
		players.push_back(player);
		break;
	}
}

void PlayState::render(SpriteBatch& batch) {
	board->render(batch);
}

void PlayState::procEvent(SDL_Event& nextEvent) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (nextEvent.type == SDL_MOUSEBUTTONDOWN) {
		if (board->getDevMode()) {
			handleMouseDev(x, y, nextEvent.button.button);
		}
		else {
			handleMouse(x, y, nextEvent.button.button);
		}
	}
	else if (nextEvent.type == SDL_KEYDOWN) {
		handleKeys(x, y, nextEvent.key.keysym.sym);
	}
}

void PlayState::handleKeys(int x, int y, SDL_Keycode key) {
	switch (key) {
	case SDLK_d:
		std::cout << "Developer mode: " << std::boolalpha << !board->getDevMode() << std::endl;
		board->setDevMode(!board->getDevMode());
		break;
	case SDLK_s:
		board->save("default.sav");
		break;
	case SDLK_l:
		board->load("default.sav");
		break;
	case SDLK_DELETE:
		if (board->getDevMode()) {
			BoardPos coords = board->mouseToBoard(glm::vec2(x, y));
			if (coords != BoardPos{ -1, -1 }) {
				board->deletePiece(coords);
			}
		}
		break;
	case SDLK_k:
		if (board->getDevMode()) {
			BoardPos coords = board->mouseToBoard(glm::vec2(x, y));
			if (coords != BoardPos{ -1, -1 }) {
				Piece * picked = board->getPieceAt(coords);
				if (picked != nullptr) {
					picked->setKing(!picked->getKing());
				}
			}
		}
	case SDLK_i:
		if (board->getDevMode()) {
			BoardPos coords = board->mouseToBoard(glm::vec2(x, y));
			if (coords != BoardPos{ -1, -1 }) {
				Piece * picked = board->getPieceAt(coords);
				if (picked != nullptr) {
					picked->logInfo();
				}
			}
		}
	}
}

void PlayState::handleMouse(int x, int y, int button) {
	BoardPos boardCoords = board->mouseToBoard(glm::vec2(x, y));
	Piece * clicked = nullptr;
	if (boardCoords != BoardPos{ -1, -1 }) {
		clicked = board->getPieceAt(boardCoords);
		if (clicked == nullptr) { //if clicked on empty square or outside of board
			if (board->getSelected() != nullptr) {
				if (board->movePiece(Move(board->getSelected()->getPos(), boardCoords))) { //If piece was moved
					nextTurn(); //go to the next turn
				}
			}
			board->setSelected(nullptr);
		}
	}
	if (clicked == board->getSelected()) { //if clicked on selected piece
		board->setSelected(nullptr); //deselect current piece
	}
	else if (clicked->getColor() == turn) { //clicked on an unselected piece
		board->setSelected(clicked); //select clicked piece
	}
}

void PlayState::handleMouseDev(int x, int y, int button) {
	BoardPos boardCoords = board->mouseToBoard(glm::vec2(x, y));
	std::cout << "Row: " << boardCoords.row << " Col: " << boardCoords.col << std::endl;
	if (boardCoords != BoardPos{ -1, -1 }) {
		switch (button) {
		case SDL_BUTTON_LEFT:
			board->addPiece(boardCoords, PieceColor::WHITE, false);
			break;
		case SDL_BUTTON_RIGHT:
			board->addPiece(boardCoords, PieceColor::BLACK, false);
			break;
		}
	}
}

void PlayState::nextTurn() {
	//Toggle color
	if (turn == PieceColor::WHITE) {
		turn = PieceColor::BLACK;
	}
	else {
		turn = PieceColor::WHITE;
	}
	updateNeeded = true;
}