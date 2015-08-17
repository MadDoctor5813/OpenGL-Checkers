#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

#include "Engine\ShaderManager.h"
#include "Engine\TextureManager.h"
#include "Engine\SaveManager.h"
#include "Engine\Camera2D.h"
#include "Engine\SpriteBatch.h"
#include "Engine\IndexedRenderer.h"
#include "Piece.h"
#include "PlayState.h"

class App {

public:
	App();
	~App();

	void init();
	void runLoop();
	void cleanup();

	GLuint getCurrentProgram();
	ShaderManager& getShaderManager() { return shaderManager; }
	TextureManager& getTextureManager() { return textureManager; }
	SaveManager& getSaveManager() { return saveManager; }
	Camera2D& getCamera() { return camera; }
	SpriteBatch& getBatch() { return batch; }
	IndexedRenderer& getRenderer() { return renderer; }

	int screenWidth = 1024;
	int screenHeight = 720;

private:

	SDL_Window * createWindow();
	void initOpenGL();
	void initSystems();
	void initCEGUI();
	void initCEGUIResources();
	void setWndSize();
	void render();
	void procInput();

	SDL_Window * window;
	ShaderManager shaderManager;
	TextureManager textureManager;
	Camera2D camera;
	SaveManager saveManager;
	SpriteBatch batch;
	IndexedRenderer renderer;
	CEGUI::OpenGL3Renderer * guiRenderer;

	PlayState * state;

	bool exit = false;
};

