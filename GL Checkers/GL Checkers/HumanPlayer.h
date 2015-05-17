#pragma once
#include "Player.h"


class HumanPlayer : public Player {

public:
	HumanPlayer(PlayState& state, PieceColor color);
	~HumanPlayer();

	virtual void handleEvent(SDL_Event nextEvent);
};

