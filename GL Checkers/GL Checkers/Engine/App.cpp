#include <glm/glm.hpp>
#include <iostream>

#include "App.h"
#include "Engine\ShaderManager.h"
#include "Engine\SpriteRenderHelper.h"
#include "GUI.h"

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
	//init cegui
	initCEGUI();
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

void App::initCEGUI() {
	guiRenderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();
	initCEGUIResources();

}

void App::initCEGUIResources() {
	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
		(CEGUI::System::getSingleton().getResourceProvider());
	rp->setResourceGroupDirectory("schemes", "gui/schemes/");
	rp->setResourceGroupDirectory("imagesets", "gui/imagesets/");
	rp->setResourceGroupDirectory("fonts", "gui/fonts/");
	rp->setResourceGroupDirectory("layouts", "gui/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "gui/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "gui/lua_scripts/");
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

	CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
	testGui = new GUI;
	testGui->init(guiRenderer);
	testGui->setFont("DejaVuSans-10");
	testGui->loadLayout("VanillaConsole.layout");
}

void App::runLoop() {
	state = new PlayState(*this);
	state->addPlayer(PieceColor::WHITE, PlayerType::HUMAN);
	state->addPlayer(PieceColor::BLACK, PlayerType::HUMAN);
	state->enter();
	while (exit == false) {
		glClear(GL_COLOR_BUFFER_BIT);
		procInput();
		camera.update();
		state->update();
		render();
		SDL_GL_SwapWindow(window);
	}
}

void App::procInput() {
	SDL_Event nextEvent;
	while (SDL_PollEvent(&nextEvent) != 0) {
		if (nextEvent.type != SDL_QUIT && nextEvent.key.keysym.sym != SDLK_ESCAPE) {
			if (testGui->injectInput(nextEvent) == false) { //false means the gui didn't consume it and input should be passed to the game
				state->procEvent(nextEvent); //remember to move gui event processing into the state class later
			}
		}
		else {
			exit = true;
		}
	}
}

void App::render() {
	state->render(renderer);
	testGui->render();
}

void App::cleanup()  {
}



