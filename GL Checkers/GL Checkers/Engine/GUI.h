#pragma once

#include <CEGUI/GUIContext.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

#include "App.h"

class GUI {

public:
	GUI();
	~GUI();

	void init(CEGUI::OpenGL3Renderer* renderer);

	void render();
	void setFont(const std::string& font);

	CEGUI::Window* addWidget(const std::string& type, const std::string& name, const glm::vec4 & destAbs, const glm::vec4 & destRel);

private:
	CEGUI::GUIContext* context;
	CEGUI::OpenGL3Renderer* renderer;
	CEGUI::Window* root;
};

