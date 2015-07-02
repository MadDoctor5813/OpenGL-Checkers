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
		handleMouse(x, y, nextEvent.button.button);
	}
	else if (nextEvent.type == SDL_KEYDOWN) {
		handleKeys(x, y, nextEvent.key.keysym.sym);
	}
}

void HumanPlayer::handleKeys(int x, int y, SDL_Keycode key) {
	Board& board = stateRef.getBoard();
	if (key == SDLK_m) {
		Piece * picked = board.getClickedPiece(x, y);
		if (picked != nullptr) {
			picked->logInfo();
		}
	}
}

void HumanPlayer::handleMouse(int x, int y, int button) {
	Board& board = stateRef.getBoard();
	Piece * clicked = board.getClickedPiece(x, y);
	if (clicked == nullptr) { //If clicked on board or outside of board
		if (board.getSelected() != nullptr) { //if we have a piece selected
			BoardPos pos = board.mouseToBoard(glm::vec2(x, y));
			bool moveResult = board.movePiece(Move{ board.getSelected()->getPos(), pos });
			board.setSelected(nullptr); //deselect piece whether or not we moved
			if (moveResult) {
				stateRef.endTurn();
			}
		}
	}
	else if (clicked->getColor() == color) { //clicked a piece
		board.setSelected(clicked); //set the selected piece to the one we just clicked on
	}
}
