#include <glm/glm.hpp>
#include <iostream>

#include "App.h"
#include "Engine\ShaderManager.h"

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
	SDL_Window * window = SDL_CreateWindow("OpenGL Checkers Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_GetWindowSize(window, &screenWidth, &screenHeight); //set height and width properly for the rest of the game
	return window;
}

void App::initOpenGL() {
	//Create OpenGl context
	SDL_GLContext context = SDL_GL_CreateContext(window);
	//Init glew
	glewInit();
	//Turn on double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//Set background
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
	//Enable texturing
	glEnable(GL_TEXTURE_2D);
	//Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Print OpenGL info
	std::cout << "OpenGL Version String: " << glGetString(GL_VERSION) << std::endl;
}

void App::setWndSize() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	screenHeight = h;
	screenWidth = w;
}

void App::initSystems() {
	shaderManager.loadPrograms();
	textureManager.loadTextures();
	//Init the camera
	camera.init(screenWidth, screenHeight);
	camera.setScale(1.0f);

}


void App::runLoop() {
	state = new PlayState(*this);
	state->addPlayer(PieceColor::WHITE, PlayerType::HUMAN);
	state->addPlayer(PieceColor::BLACK, PlayerType::HUMAN);
	state->enter();
	while (exit == false) {
		glClear(GL_COLOR_BUFFER_BIT);
		procInput();
		render();
		camera.update();
		state->update();
		SDL_GL_SwapWindow(window);
	}
}

void App::procInput() {
	SDL_Event nextEvent;
	while (SDL_PollEvent(&nextEvent) != 0) {
		if (nextEvent.type != SDL_QUIT && nextEvent.key.keysym.sym != SDLK_ESCAPE) {
			state->procEvent(nextEvent);
		}
		else {
			cleanup();
			exit = true;
		}
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
	state->render();

}

void App::cleanup()  {
	
}



