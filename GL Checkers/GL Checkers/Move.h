#pragma once

#include "BoardPos.h"

struct Move {
	BoardPos oldPos;
	BoardPos newPos;

	Move(BoardPos oldPos, BoardPos newPos) : oldPos(oldPos), newPos(newPos) {}

	bool operator== (Move& rhs) const {
		return (oldPos == rhs.oldPos && newPos == rhs.newPos);
	}

	bool operator== (Move& rhs) {
		return (oldPos == rhs.oldPos && newPos == rhs.newPos);
	}
};
