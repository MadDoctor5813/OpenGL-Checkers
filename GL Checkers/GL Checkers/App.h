#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include "Sprite.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SaveManager.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "Piece.h"
#include "PlayState.h"

class App {

public:
	App();
	~App();

	void init();
	void runLoop();

	GLuint getCurrentProgram();
	ShaderManager& getShaderManager() { return shaderManager; }
	TextureManager& getTextureManager() { return textureManager; }
	SaveManager& getSaveManager() { return saveManager; }
	Camera2D& getCamera() { return camera; }
	SpriteBatch& getBatch() { return batch; }

	int screenWidth = 1024;
	int screenHeight = 720;

private:

	SDL_Window * createWindow();
	void initOpenGL();
	void initSystems();
	void setWndSize();
	void render();
	void procInput();
	void cleanup();

	SDL_Window * window;
	ShaderManager shaderManager;
	TextureManager textureManager;
	Camera2D camera;
	SaveManager saveManager;
	SpriteBatch batch;

	PlayState * state;

	bool exit = false;
};

