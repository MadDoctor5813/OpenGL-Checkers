#include <glm/glm.hpp>

#include "App.h"
#include "ShaderManager.h"

App::App() { 

}

App::~App() {

}

void App::init() {
	//Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Init window
	window = createWindow();
	//Init openGL 
	initOpenGL();
	//init managers
	initSystems();
}

SDL_Window * App::createWindow() {
	return SDL_CreateWindow("OpenGL Checkers Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
}

void App::initOpenGL() {
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
	//Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void App::initSystems() {
	shaderManager.loadPrograms();
	textureManager.loadTextures();
	//Init the camera
	camera.init(screenWidth, screenHeight);
	camera.setScale(1.0f);

}


void App::runLoop() {
	testBoard = new Board(*this);
	while (exit == false) {
		glClear(GL_COLOR_BUFFER_BIT);
		procInput();
		render();
		camera.update();
		SDL_GL_SwapWindow(window);
	}
}

void App::procInput() {
	float const CAMERA_SPEED = 10.0f;
	float const ZOOM_SPEED = 0.1f;
	SDL_Event nextEvent;
	SDL_PollEvent(&nextEvent);
	if (nextEvent.type == SDL_QUIT) {
		cleanup();
		exit = true;
	}
}

void App::render() {
	glActiveTexture(GL_TEXTURE0);
	ShaderProgram& shader = getShaderManager().getShader("spriteShading");
	shader.enable();
	GLint camTransformLoc = glGetUniformLocation(shader.getProgram(), "camTransform");
	GLint textureLoc = glGetUniformLocation(shader.getProgram(), "spriteTexture");
	glUniformMatrix4fv(camTransformLoc, 1, GL_FALSE, &(camera.getMatrix()[0][0]));
	glUniform1i(textureLoc, 0);

	batch.init();
	batch.begin();
	testBoard->render(batch);
	batch.end();

	batch.render();

}

void App::cleanup()  {
	//Place for cleanup operations in the future?
}



