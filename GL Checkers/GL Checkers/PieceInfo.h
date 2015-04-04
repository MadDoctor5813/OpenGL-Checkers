#pragma once

#include "PieceColor.h"

struct SavedPiece { //Represents one piece saved in a square
	PieceColor color; //0 is white, 1 is black
	bool king; //0 is regular, 1 is king
};