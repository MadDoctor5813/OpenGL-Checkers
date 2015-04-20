#pragma once

#include "BoardPos.h"

struct Move {
	BoardPos oldPos;
	BoardPos newPos;

	Move(BoardPos oldPos, BoardPos newPos) : oldPos(oldPos), newPos(newPos) {}
};