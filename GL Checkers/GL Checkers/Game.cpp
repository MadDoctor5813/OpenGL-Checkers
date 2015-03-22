#include <glm/glm.hpp>

#include "Game.h"
#include "ShaderManager.h"

Game::Game() { 

}

Game::~Game() {

}

GLuint Game::getCurrentProgram() {
	return currentProgram.getProgram();
}

TextureManager& Game::getTextureManager() {
	return textureManager;
}

Camera2D& Game::getCamera() {
	return camera;
}

void Game::init() {
	//Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Init window
	window = createWindow();
	//Init openGL 
	initOpenGL();
	//init managers
	initSystems();
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Enable texturing
	glEnable(GL_TEXTURE_2D);
}

void Game::initSystems() {
	shaderManager.loadPrograms();
	//Activate shader
	ShaderProgram testProgram = shaderManager.getShader("spriteShading");
	testProgram.addAttr("vertPos");
	testProgram.addAttr("vertTexPos");
	testProgram.addAttr("vertColor");
	testProgram.enable();
	currentProgram = testProgram;
	textureManager.loadTextures();
	//Init the camera
	camera.init(screenWidth, screenHeight);
	camera.setScale(1.0f);

}


void Game::runLoop() {

	float const CAMERA_SPEED = 10.0f;
	float const ZOOM_SPEED = 0.1f;

	Sprite testSprite = Sprite(0.0f, 0.0f, 64.0f, 64.0f, *this);
	SDL_Event nextEvent;
	while (exit == false) {
		glClear(GL_COLOR_BUFFER_BIT);
		camera.update();
		SDL_PollEvent(&nextEvent);
		if (nextEvent.type == SDL_QUIT) {
			cleanup();
			exit = true;
		}
		if (nextEvent.type == SDL_KEYDOWN) {
			switch (nextEvent.key.keysym.sym) {
			case SDLK_w:
				camera.translate(glm::vec2(0.0f, CAMERA_SPEED));
				break;
			case SDLK_s:
				camera.translate(glm::vec2(0.0f, -CAMERA_SPEED));
				break;
			case SDLK_a:
				camera.translate(glm::vec2(CAMERA_SPEED, 0.0f));
				break;
			case SDLK_d:
				camera.translate(glm::vec2(-CAMERA_SPEED, 0.0f));
				break;
			case SDLK_q:
				camera.zoom(-ZOOM_SPEED);
				break;
			case SDLK_e:
				camera.zoom(ZOOM_SPEED);
			}
		}
		testSprite.draw();
		SDL_GL_SwapWindow(window);
	}
}

void Game::cleanup()  {
	//Place for cleanup operations in the future?
}



