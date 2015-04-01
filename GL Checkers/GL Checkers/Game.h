#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include "Sprite.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Camera2D.h"
#include "SpriteBatch.h"

class Game {

public:
	Game();
	~Game();

	void init();
	void runLoop();

	GLuint getCurrentProgram();
	ShaderManager& getShaderManager() { return shaderManager; }
	TextureManager& getTextureManager() { return textureManager; }
	Camera2D& getCamera() { return camera; }

private:
	SDL_Window * createWindow();
	void initOpenGL();
	void initSystems();
	void render();
	void procInput();
	void cleanup();

	SDL_Window * window;
	ShaderManager shaderManager;
	TextureManager textureManager;
	Camera2D camera;
	SpriteBatch batch;

	ShaderProgram currentProgram;


	bool exit = false;
	int screenWidth = 1024;
	int screenHeight = 720;
};

