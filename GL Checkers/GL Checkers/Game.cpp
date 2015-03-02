#include "Game.h"


Game::Game()  { 
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
	glClearColor(0, 0, 0, 0);
	//Load program
	ShaderProgram program("colorShading.vert", "colorShading.frag");
	glUseProgram(program.getProgram());
}


void Game::runLoop() {
	Sprite testSprite = Sprite(-1.0f, -1.0f, 1.0f, 1.0f);
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
		testSprite.draw();
		SDL_GL_SwapWindow(window);
	}
}

void Game::cleanup()  {
	//Place for cleanup operations in the future?
}



