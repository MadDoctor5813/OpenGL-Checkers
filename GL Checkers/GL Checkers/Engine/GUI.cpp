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
		case SDL_TEXTINPUT:
			consumed |= injectKeyEvent(injected);
			break;
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

bool GUI::injectKeyEvent(SDL_Event & injected) {
	bool consumed = false;
	switch (injected.type) {
	case SDL_KEYUP:
		consumed |= context->injectKeyDown(toCEGUIKey(injected.key.keysym.sym));
		break;
	case SDL_KEYDOWN:
		consumed |= context->injectKeyDown(toCEGUIKey(injected.key.keysym.sym));
		break;
	case SDL_TEXTINPUT: 
		//need a scope here, because we're creating variables here now
		{ 
			CEGUI::utf32 codePoint = 0;
			for (int i = 0; injected.text.text[i] != '\0'; i++) { //loops through all chars in the event field
				codePoint |= (((CEGUI::utf32)injected.text.text[i]) << (i * 8)); //constuct unicode character from each char
			}
			consumed |= context->injectChar(codePoint);
			break;
		}
	}
	return consumed;
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

CEGUI::Key::Scan GUI::toCEGUIKey(SDL_Keycode key) {
	//taken from http://cegui.org.uk/wiki/SDL_to_CEGUI_keytable
	using namespace CEGUI;
	switch (key) {
	case SDLK_BACKSPACE:    return Key::Backspace;
	case SDLK_TAB:          return Key::Tab;
	case SDLK_RETURN:       return Key::Return;
	case SDLK_PAUSE:        return Key::Pause;
	case SDLK_ESCAPE:       return Key::Escape;
	case SDLK_SPACE:        return Key::Space;
	case SDLK_COMMA:        return Key::Comma;
	case SDLK_MINUS:        return Key::Minus;
	case SDLK_PERIOD:       return Key::Period;
	case SDLK_SLASH:        return Key::Slash;
	case SDLK_0:            return Key::Zero;
	case SDLK_1:            return Key::One;
	case SDLK_2:            return Key::Two;
	case SDLK_3:            return Key::Three;
	case SDLK_4:            return Key::Four;
	case SDLK_5:            return Key::Five;
	case SDLK_6:            return Key::Six;
	case SDLK_7:            return Key::Seven;
	case SDLK_8:            return Key::Eight;
	case SDLK_9:            return Key::Nine;
	case SDLK_COLON:        return Key::Colon;
	case SDLK_SEMICOLON:    return Key::Semicolon;
	case SDLK_EQUALS:       return Key::Equals;
	case SDLK_LEFTBRACKET:  return Key::LeftBracket;
	case SDLK_BACKSLASH:    return Key::Backslash;
	case SDLK_RIGHTBRACKET: return Key::RightBracket;
	case SDLK_a:            return Key::A;
	case SDLK_b:            return Key::B;
	case SDLK_c:            return Key::C;
	case SDLK_d:            return Key::D;
	case SDLK_e:            return Key::E;
	case SDLK_f:            return Key::F;
	case SDLK_g:            return Key::G;
	case SDLK_h:            return Key::H;
	case SDLK_i:            return Key::I;
	case SDLK_j:            return Key::J;
	case SDLK_k:            return Key::K;
	case SDLK_l:            return Key::L;
	case SDLK_m:            return Key::M;
	case SDLK_n:            return Key::N;
	case SDLK_o:            return Key::O;
	case SDLK_p:            return Key::P;
	case SDLK_q:            return Key::Q;
	case SDLK_r:            return Key::R;
	case SDLK_s:            return Key::S;
	case SDLK_t:            return Key::T;
	case SDLK_u:            return Key::U;
	case SDLK_v:            return Key::V;
	case SDLK_w:            return Key::W;
	case SDLK_x:            return Key::X;
	case SDLK_y:            return Key::Y;
	case SDLK_z:            return Key::Z;
	case SDLK_DELETE:       return Key::Delete;
	case SDLK_KP_PERIOD:    return Key::Decimal;
	case SDLK_KP_DIVIDE:    return Key::Divide;
	case SDLK_KP_MULTIPLY:  return Key::Multiply;
	case SDLK_KP_MINUS:     return Key::Subtract;
	case SDLK_KP_PLUS:      return Key::Add;
	case SDLK_KP_ENTER:     return Key::NumpadEnter;
	case SDLK_KP_EQUALS:    return Key::NumpadEquals;
	case SDLK_UP:           return Key::ArrowUp;
	case SDLK_DOWN:         return Key::ArrowDown;
	case SDLK_RIGHT:        return Key::ArrowRight;
	case SDLK_LEFT:         return Key::ArrowLeft;
	case SDLK_INSERT:       return Key::Insert;
	case SDLK_HOME:         return Key::Home;
	case SDLK_END:          return Key::End;
	case SDLK_PAGEUP:       return Key::PageUp;
	case SDLK_PAGEDOWN:     return Key::PageDown;
	case SDLK_F1:           return Key::F1;
	case SDLK_F2:           return Key::F2;
	case SDLK_F3:           return Key::F3;
	case SDLK_F4:           return Key::F4;
	case SDLK_F5:           return Key::F5;
	case SDLK_F6:           return Key::F6;
	case SDLK_F7:           return Key::F7;
	case SDLK_F8:           return Key::F8;
	case SDLK_F9:           return Key::F9;
	case SDLK_F10:          return Key::F10;
	case SDLK_F11:          return Key::F11;
	case SDLK_F12:          return Key::F12;
	case SDLK_F13:          return Key::F13;
	case SDLK_F14:          return Key::F14;
	case SDLK_F15:          return Key::F15;
	case SDLK_RSHIFT:       return Key::RightShift;
	case SDLK_LSHIFT:       return Key::LeftShift;
	case SDLK_RCTRL:        return Key::RightControl;
	case SDLK_LCTRL:        return Key::LeftControl;
	case SDLK_RALT:         return Key::RightAlt;
	case SDLK_LALT:         return Key::LeftAlt;
	case SDLK_SYSREQ:       return Key::SysRq;
	case SDLK_MENU:         return Key::AppMenu;
	case SDLK_POWER:        return Key::Power;
	default:                return Key::Unknown;
	}
}
