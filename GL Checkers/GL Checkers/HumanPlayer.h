#pragma once
#include "Player.h"


class HumanPlayer : public Player {

public:
	HumanPlayer(PlayState& state, PieceColor color);
	~HumanPlayer();

	virtual void handleEvent(SDL_Event nextEvent);

private:
	void handleKeys(int x, int y, SDL_Keycode key);
	void handleMouse(int x, int y, int button);
	void handleMouseDev(int x, int y, int button);


};

