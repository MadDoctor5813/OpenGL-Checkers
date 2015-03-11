#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include "Sprite.h"
#include "ShaderProgram.h"
#include "ShaderManager.h"

class Game {

public:
	Game();
	~Game();
	void init();
	void runLoop();

private:
	SDL_Window * createWindow();
	void initOpenGL();
	void initManagers();
	void testDraw();
	void cleanup();

	SDL_Window * window;
	ShaderManager shaderManager;

	bool exit = false;
	int screenWidth = 1024;
	int screenHeight = 720;
};

