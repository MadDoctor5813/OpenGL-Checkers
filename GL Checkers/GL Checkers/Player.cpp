#include "Player.h"


Player::Player(PlayState& state) : stateRef(state) {

}


Player::~Player() {

}

void Player::startTurn() {
	active = true;
}

void Player::endTurn() {
	active = false;
}
