#include "Player.h"


Player::Player(PlayState& state, PieceColor color) : stateRef(state), color(color) {

}


Player::~Player() {

}

void Player::startTurn() {
	active = true;
}

void Player::endTurn() {
	active = false;
}
