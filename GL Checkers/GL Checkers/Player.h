#pragma once

#include "PieceColor.h"
#include "PlayState.h"

class Player {

public:
	Player(PlayState& state, PieceColor color);
	~Player();

	void startTurn();
	void endTurn();

	virtual void handleEvent(SDL_Event nextEvent) = 0;

	PieceColor color;

protected:
	PlayState& stateRef;

	bool active;

	int numPieces;
	bool canJump;
};

