#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include "EventHandler.h"

class Game {

public:
	Game();
	~Game();
	void runLoop();

private:
	SDL_Window * createWindow();
	void initOpenGL();
	void testDraw();
	void cleanup();

	SDL_Window * window;
	EventHandler handler;

	bool exit = false;
	int screenWidth = 1024;
	int screenHeight = 720;
};

