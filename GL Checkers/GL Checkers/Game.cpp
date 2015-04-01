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
	textureManager.loadTextures();
	//Init the camera
	camera.init(screenWidth, screenHeight);
	camera.setScale(1.0f);

}


void Game::runLoop() {
	while (exit == false) {
		glClear(GL_COLOR_BUFFER_BIT);
		procInput();
		render();
		camera.update();
		SDL_GL_SwapWindow(window);
	}
}

void Game::procInput() {
	float const CAMERA_SPEED = 10.0f;
	float const ZOOM_SPEED = 0.1f;
	SDL_Event nextEvent;
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
}

void Game::render() {
	glActiveTexture(GL_TEXTURE0);
	ShaderProgram& shader = getShaderManager().getShader("spriteShading");
	shader.enable();
	GLuint tacoTex = getTextureManager().getTexture("taco");
	GLint camTransformLoc = glGetUniformLocation(shader.getProgram(), "camTransform");
	GLint textureLoc = glGetUniformLocation(shader.getProgram(), "spriteTexture");
	glUniformMatrix4fv(camTransformLoc, 1, GL_FALSE, &(camera.getMatrix()[0][0]));
	glUniform1i(textureLoc, 0);

	batch.init();
	batch.begin();

	glm::vec4 testPos(128.0f, 128.0f, 64.0f, 64.0f);
	glm::vec4 testUv(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 testPos2(256.0f, 256.0f, 64.0f, 64.0f);
	glm::vec4 testUv2(0.0f, 0.0f, 1.0f, 1.0f);

	batch.draw(testPos, testUv, tacoTex, 0, Color{ 255, 255, 255, 255 });
	batch.draw(testPos2, testUv2, tacoTex, 0, Color{ 255, 255, 255, 255 });

	batch.end();

	batch.render();

}

void Game::cleanup()  {
	//Place for cleanup operations in the future?
}



