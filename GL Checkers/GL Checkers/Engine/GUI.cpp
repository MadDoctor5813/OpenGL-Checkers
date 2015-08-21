#include "GUI.h"

#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

GUI::GUI(){
}

GUI::~GUI() {
}

void GUI::init(CEGUI::OpenGL3Renderer* renderer) {
	context = &CEGUI::System::getSingleton().createGUIContext(renderer->getDefaultRenderTarget());
	root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	root->setSize(CEGUI::USize(CEGUI::UDim(1.0f, 0), CEGUI::UDim(1.0f, 0)));
	root->setMousePassThroughEnabled(true);
	context->setRootWindow(root);
}

void GUI::render() {
	CEGUI::System::getSingleton().getRenderer()->beginRendering();
	context->draw();
	CEGUI::System::getSingleton().getRenderer()->endRendering();
	glDisable(GL_SCISSOR_TEST);
}

void GUI::setFont(const std::string& font) {
	CEGUI::FontManager::getSingleton().createFromFile(font + ".font");
	context->setDefaultFont(font);
}

void GUI::loadLayout(const std::string & layout) {
	CEGUI::Window* layoutRoot = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(layout);
	root->addChild(layoutRoot);
}

bool GUI::injectInput(SDL_Event & injected) {
	bool consumed = false; //if any one of the injection functions returns true, consumed will be true, courtesy of the or operator
	switch (injected.type) {
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEMOTION:
			consumed |= injectMouseEvent(injected);
			break;
		case SDL_KEYUP:
		case SDL_KEYDOWN:
			injectKeyPress(injected);
	}
	return consumed;
}

CEGUI::Window* GUI::addWidget(const std::string & type, const std::string & name, const glm::vec4 & destAbs, const glm::vec4 & destRel) {
	CEGUI::Window* widget = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	root->addChild(widget);
	CEGUI::UVector2 pos = CEGUI::UVector2(CEGUI::UDim(destRel.x, destAbs.x), CEGUI::UDim(destRel.y, destAbs.y));
	CEGUI::USize size = CEGUI::USize(CEGUI::UDim(destRel.z, destAbs.z), CEGUI::UDim(destRel.w, destAbs.w));
	widget->setPosition(pos);
	widget->setSize(size);
	return widget;
}

bool GUI::injectMouseEvent(SDL_Event & injected) {
	bool consumed = false; //if any one of the injection functions returns true, consumed will be true, courtesy of the or operator
	switch (injected.type) {
	case SDL_MOUSEBUTTONUP:
		consumed |= context->injectMouseButtonUp(toCEGUIButton(injected.button.button));
		break;
	case SDL_MOUSEBUTTONDOWN:
		consumed |= context->injectMouseButtonDown(toCEGUIButton(injected.button.button));
		break;
	case SDL_MOUSEMOTION:
		consumed |= context->injectMousePosition(injected.motion.x, injected.motion.y);
		break;
	}
	return consumed;
}

bool GUI::injectKeyPress(SDL_Event & injected) {
	return false;
}

CEGUI::MouseButton GUI::toCEGUIButton(Uint8 button) {
	switch (button) {
	case SDL_BUTTON_LEFT:
		return CEGUI::LeftButton;
		break;
	case SDL_BUTTON_RIGHT:
		return CEGUI::RightButton;
		break;
	case SDL_BUTTON_MIDDLE:
		return CEGUI::MiddleButton;
		break;
	}
}
