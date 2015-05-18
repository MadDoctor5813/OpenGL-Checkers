#include "HumanPlayer.h"
#include "Piece.h"


HumanPlayer::HumanPlayer(PlayState& state, PieceColor color) : Player(state, color) {
	
}


HumanPlayer::~HumanPlayer() {

}

void HumanPlayer::handleEvent(SDL_Event nextEvent) {
	Board& board = stateRef.getBoard();
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (nextEvent.type == SDL_MOUSEBUTTONDOWN) {
		if (board.getDevMode()) {
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

void HumanPlayer::handleKeys(int x, int y, SDL_Keycode key) {

}

void HumanPlayer::handleMouse(int x, int y, int button) {
	Board& board = stateRef.getBoard();
	BoardPos boardCoords = board.mouseToBoard(glm::vec2(x, y));
	Piece * clicked = nullptr;
	if (boardCoords != BoardPos{ -1, -1 }) {
		clicked = board.getPieceAt(boardCoords);
		if (clicked == nullptr) { //if clicked on empty square or outside of board
			if (board.getSelected() != nullptr) {
				if (board.movePiece(Move(board.getSelected()->getPos(), boardCoords))) { //If piece was moved
					stateRef.endTurn();
				}
			}
			board.setSelected(nullptr);
		}
	}
	if (clicked == board.getSelected()) { //if clicked on selected piece
		board.setSelected(nullptr); //deselect current piece
	}
	else if (clicked->getColor() == color) { //clicked on an unselected piece
		board.setSelected(clicked); //select clicked piece
	}
}

void HumanPlayer::handleMouseDev(int x, int y, int button) {
	Board& board = stateRef.getBoard();
	BoardPos boardCoords = board.mouseToBoard(glm::vec2(x, y));
	std::cout << "Row: " << boardCoords.row << " Col: " << boardCoords.col << std::endl;
	if (boardCoords != BoardPos{ -1, -1 }) {
		switch (button) {
		case SDL_BUTTON_LEFT:
			board.addPiece(boardCoords, PieceColor::WHITE, false);
			break;
		case SDL_BUTTON_RIGHT:
			board.addPiece(boardCoords, PieceColor::BLACK, false);
			break;
		}
	}
}