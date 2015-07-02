#pragma once
#include <SDL.h>

#include "Engine\SpriteBatch.h"

class GameState {

public:
	GameState();
	~GameState();

	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual void render(SpriteBatch& batch) = 0;
	virtual void procEvent(SDL_Event& nextEvent) = 0;
	virtual void update() = 0;

};

