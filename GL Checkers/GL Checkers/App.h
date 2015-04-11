#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include "Sprite.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SaveFileManager.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "Piece.h"

class App {

public:
	App();
	~App();

	void init();
	void runLoop();

	GLuint getCurrentProgram();
	ShaderManager& getShaderManager() { return shaderManager; }
	TextureManager& getTextureManager() { return textureManager; }
	Camera2D& getCamera() { return camera; }
	SpriteBatch& getBatch() { return batch; }

	const int SQUARE_SIZE = 64;
	int screenWidth = 1024;
	int screenHeight = 720;

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
	SaveFileManager saveManager;
	SpriteBatch batch;

	Board * testBoard;

	bool exit = false;
};

