#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include "Sprite.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Camera2D.h"

class Game {

public:
	Game();
	~Game();

	void init();
	void runLoop();

	GLuint getCurrentProgram();
	TextureManager& getTextureManager();
	Camera2D& getCamera();

private:
	SDL_Window * createWindow();
	void initOpenGL();
	void initSystems();
	void testDraw();
	void cleanup();

	SDL_Window * window;
	ShaderManager shaderManager;
	TextureManager textureManager;
	Camera2D camera;

	ShaderProgram currentProgram;


	bool exit = false;
	int screenWidth = 1024;
	int screenHeight = 720;
};

