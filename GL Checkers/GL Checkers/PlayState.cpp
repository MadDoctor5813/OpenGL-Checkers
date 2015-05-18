#include "PlayState.h"
#include "Piece.h"
#include "HumanPlayer.h"


PlayState::PlayState(App& app) : appRef(app){

}


PlayState::~PlayState() {
	for (auto player : players) {
		delete player;
	}
}

void PlayState::enter() {
	board = new Board(appRef);
	board->load("default.sav");
	activePlayer = 0;
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
	getPlayer(activePlayer)->handleEvent(nextEvent);
}


void PlayState::endTurn() {
	updateNeeded = true;
	activePlayer++;
	activePlayer = activePlayer % players.size();
}


