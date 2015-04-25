#pragma once

#include "BoardPos.h"

struct Move {
	BoardPos oldPos;
	BoardPos newPos;

	bool isCapture;
	BoardPos capTarget;

	Move(BoardPos oldPos, BoardPos newPos, bool isCapture = false, BoardPos capTarget = { -1, -1 }) : oldPos(oldPos), newPos(newPos), isCapture(isCapture), capTarget(capTarget) {}

	bool operator== (Move& rhs) const {
		return (oldPos == rhs.oldPos && newPos == rhs.newPos);
	}

	bool operator== (Move& rhs) {
		return (oldPos == rhs.oldPos && newPos == rhs.newPos);
	}
};
