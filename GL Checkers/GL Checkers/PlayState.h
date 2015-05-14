#pragma once
#include "GameState.h"
#include "Board.h"

class PlayState : public GameState {

public:
	PlayState(App& app);
	~PlayState();

	virtual void enter();
	virtual void exit();
	virtual void render(SpriteBatch& batch);
	virtual void procEvent(SDL_Event& nextEvent);
	virtual void update();

private:
	Board * board;
	App& appRef;

	PieceColor turn = PieceColor::WHITE;

	bool updateNeeded = true;


	void handleKeys(int x, int y, SDL_Keycode key);
	void handleMouse(int x, int y, int button);
	void handleMouseDev(int x, int y, int button);

	void nextTurn();
};

