#include <glm/glm.hpp>
#include <iostream>

#include "App.h"
#include "Engine\ShaderManager.h"
#include "Engine\SpriteRenderHelper.h"

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
	//init librocket
	initLibrocket();
}

SDL_Window * App::createWindow() {
	SDL_Window * window = SDL_CreateWindow("OpenGL Checkers Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 720, SDL_WINDOW_OPENGL);
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
	renderer.init(*this);
}

void App::initLibrocket() {
	renderInterface = new GUIRenderInterface(*this);
	systemInterface = new GUISystemInterface; //these should die when the game does
	Rocket::Core::SetSystemInterface(systemInterface);
	Rocket::Core::SetRenderInterface(renderInterface);
	if (Rocket::Core::Initialise() == false) {
		std::cout << "libRocket init error" << std::endl;
	}
	rocketContext = Rocket::Core::CreateContext("OpenGL Checkers Game", Rocket::Core::Vector2i(screenWidth, screenHeight));
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
	state->render(renderer);
}

void App::cleanup()  {
	
}



