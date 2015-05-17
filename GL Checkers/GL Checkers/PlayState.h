#pragma once

#include "GameState.h"
#include "Board.h"
#include "Player.h"
#include "PlayerType.h"

class PlayState : public GameState {

public:
	PlayState(App& app);
	~PlayState();

	virtual void enter();
	virtual void exit();
	virtual void render(SpriteBatch& batch);
	virtual void procEvent(SDL_Event& nextEvent);
	virtual void update();

	void addPlayer(PieceColor color, PlayerType type);

	Board& getBoard() { return *board; }

private:
	Board * board;
	App& appRef;

	std::vector<Player*> players;

	bool updateNeeded = true;

	void handleKeys(int x, int y, SDL_Keycode key);
	void handleMouse(int x, int y, int button);
	void handleMouseDev(int x, int y, int button);

	void nextTurn();
};

