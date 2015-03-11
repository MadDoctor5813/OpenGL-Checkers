#include <SDL.h>
#include <iostream>

#include "Game.h"
#include "ShaderProgram.h"

//Entry point
int main(int argc, char** argv) {
	Game game = Game();
	game.init();
	game.runLoop();
	return 0;
}