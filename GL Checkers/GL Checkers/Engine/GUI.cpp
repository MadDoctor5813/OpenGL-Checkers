#include "GUI.h"

GUI::GUI(){
}

GUI::~GUI() {
}

void GUI::init(CEGUI::OpenGL3Renderer* renderer) {
	context = &CEGUI::System::getSingleton().createGUIContext(renderer->getDefaultRenderTarget());
	root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
}

void GUI::render() {
	context->draw();
}

void GUI::setFont(const std::string& font) {
	CEGUI::FontManager::getSingleton().createFromFile(font + ".font");
	context->setDefaultFont(font);
}

CEGUI::Window* GUI::addWidget(const std::string & type, const std::string & name, const glm::vec4 & destAbs, const glm::vec4 & destRel) {
	CEGUI::Window* widget = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	CEGUI::UVector2 pos = CEGUI::UVector2(CEGUI::UDim(destRel.x, destAbs.x), CEGUI::UDim(destRel.y, destAbs.y));
	CEGUI::USize size = CEGUI::USize(CEGUI::UDim(destRel.z, destAbs.w), CEGUI::UDim(destRel.z, destAbs.w));
	widget->setPosition(pos);
	widget->setSize(size);
	return widget;
}
