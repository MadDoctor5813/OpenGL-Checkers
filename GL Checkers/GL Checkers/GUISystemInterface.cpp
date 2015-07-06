#include "GUISystemInterface.h"

#include <SDL.h>

GUISystemInterface::GUISystemInterface() {
}


GUISystemInterface::~GUISystemInterface() {
}

float GUISystemInterface::GetElapsedTime() {
	return SDL_GetTicks() * 1000;
}