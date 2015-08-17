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
}

void GUI::setFont(const std::string& font) {
	CEGUI::FontManager::getSingleton().createFromFile(font + ".font");
	context->setDefaultFont(font);
}

CEGUI::Window* GUI::addWidget(const std::string & type, const std::string & name, glm::vec4 & dest) {

}
