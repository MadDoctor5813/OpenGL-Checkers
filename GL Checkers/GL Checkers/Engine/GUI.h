#pragma once

#include <CEGUI/GUIContext.h>

namespace CEGUI { //forward declare to fix gl.h being included before glew.h
	class OpenGL3Renderer;
};

#include "App.h"

class GUI {

public:
	GUI();
	~GUI();

	void init(CEGUI::OpenGL3Renderer* renderer);

	void render();
	void setFont(const std::string& font);
	void loadLayout(const std::string& layout);

	bool injectInput(SDL_Event& injected);

	CEGUI::Window* addWidget(const std::string& type, const std::string& name, const glm::vec4 & destAbs, const glm::vec4 & destRel);

private:
	CEGUI::GUIContext* context;
	CEGUI::OpenGL3Renderer* renderer;
	CEGUI::Window* root;

	bool injectMouseEvent(SDL_Event& injected);
	bool injectKeyPress(SDL_Event& injected);

	CEGUI::MouseButton toCEGUIButton(Uint8 button);
};

