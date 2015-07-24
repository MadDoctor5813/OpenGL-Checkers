#pragma once

#include "Engine\GameState.h"
#include "Board.h"
#include "PlayerType.h"

class Player;

class PlayState : public GameState {

public:
	PlayState(App& app);
	~PlayState();

	virtual void enter();
	virtual void exit();
	virtual void render(IndexedRenderer& renderer);
	virtual void procEvent(SDL_Event& nextEvent);
	virtual void update();

	void endTurn();

	void addPlayer(PieceColor color, PlayerType type);

	Player * getPlayer(int index) { return players[index]; }

	Board& getBoard() { return *board; }

private:

	Board * board;
	App& appRef;

	std::vector<Player*> players;

	int activePlayer;

	bool updateNeeded = true;

};

