#include "HumanPlayer.h"


HumanPlayer::HumanPlayer(PlayState& state) : Player(state) {
	
}


HumanPlayer::~HumanPlayer() {

}

void HumanPlayer::handleEvent(SDL_Event nextEvent) {
	Board& board = stateRef.getBoard();
}
