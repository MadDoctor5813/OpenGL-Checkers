#include "Game.h"


Game::Game() {
	//Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Init window
	window = createWindow();
	//Init event handler
	handler = EventHandler();
	//Init OpenGL
	initOpenGL();
}



Game::~Game() {

}

SDL_Window * Game::createWindow() {
	return SDL_CreateWindow("OpenGL Checkers Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
}

void Game::initOpenGL() {
	//Create OpenGl context
	SDL_GLContext context = SDL_GL_CreateContext(window);
	//Init glew
	glewInit();
	//Turn on double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//Set background
	glClearColor(255, 0, 255, 0);
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
			handler.processEvent(nextEvent);
		}
		testDraw();
	}
}

void Game::cleanup()  {
	//Place for cleanup operations in the future?
}

void Game::testDraw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(255, 0, 0);
	glVertex2f(-1, -1);
	glVertex2f(0, 1);
	glVertex2f(1, -1);
	glEnd();

	SDL_GL_SwapWindow(window);
}


