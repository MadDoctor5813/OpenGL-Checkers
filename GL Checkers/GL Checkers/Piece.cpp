#include "Piece.h"

#include "Engine/App.h"


Piece::Piece(float x, float y, App& app) : x(x), y(y), appRef(app) {
	texture = appRef.getTextureManager().getTexture("taco");
}


Piece::~Piece() {
}

void Piece::handleEvent(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			y += 16;
			break;
		case SDLK_s:
			y -= 16;
			break;
		case SDLK_a:
			x -= 16;
			break;
		case SDLK_d:
			x += 16;
			break;
		}
	}
}

void Piece::update() {
	std::cout << "Piece updated" << std::endl;
}

void Piece::render() {
	appRef.getBatch().draw(glm::vec4(x, y, PIECE_SIZE, PIECE_SIZE), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture, 0, Color{ 255, 255, 255, 255 });
}
