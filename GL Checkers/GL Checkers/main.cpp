#include <SDL.h>
#include <iostream>

#include "Engine\App.h"
#include "Engine\ShaderProgram.h"

//Entry point
int main(int argc, char** argv) {
	App game = App();
	game.init();
	game.runLoop();
	return 0;
}