#include "Game.h"


Game::Game() {
	//Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Init window
	window = createWindow();
	//Init event handler
	handler = new EventHandler();
}



Game::~Game() {

}

SDL_Window * Game::createWindow() {
	return SDL_CreateWindow("OpenGL Checkers Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, 0);
}

void Game::runLoop() {
	SDL_Event nextEvent;
	while (exit == false) {
		SDL_PollEvent(&nextEvent);
		if (nextEvent.type == SDL_QUIT) {
			cleanup();
			exit = true;
		}
		else {
			handler->processEvent(nextEvent);
		}
	}
}

void Game::cleanup()  {
	//Place for cleanup operations in the future?
}

