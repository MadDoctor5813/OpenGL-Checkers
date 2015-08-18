#include "GUI.h"

#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

GUI::GUI(){
}

GUI::~GUI() {
}

void GUI::init(CEGUI::OpenGL3Renderer* renderer) {
	context = &CEGUI::System::getSingleton().createGUIContext(renderer->getDefaultRenderTarget());
	root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
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

CEGUI::Window* GUI::addWidget(const std::string & type, const std::string & name, const glm::vec4 & destAbs, const glm::vec4 & destRel) {
	CEGUI::Window* widget = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	root->addChild(widget);
	CEGUI::UVector2 pos = CEGUI::UVector2(CEGUI::UDim(destRel.x, destAbs.x), CEGUI::UDim(destRel.y, destAbs.y));
	CEGUI::USize size = CEGUI::USize(CEGUI::UDim(destRel.z, destAbs.z), CEGUI::UDim(destRel.w, destAbs.w));
	widget->setPosition(pos);
	widget->setSize(size);
	return widget;
}
