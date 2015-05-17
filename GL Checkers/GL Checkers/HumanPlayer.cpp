#include "HumanPlayer.h"


HumanPlayer::HumanPlayer(PlayState& state, PieceColor color) : Player(state, color) {
	
}


HumanPlayer::~HumanPlayer() {

}

void HumanPlayer::handleEvent(SDL_Event nextEvent) {
	Board& board = stateRef.getBoard();
}
