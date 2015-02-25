#pragma once

#include <SDL.h>

class EventHandler {

public:
	EventHandler();
	~EventHandler();

	void processEvent(SDL_Event e);

	bool exit = false;
};

