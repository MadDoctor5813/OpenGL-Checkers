#pragma once

#include "PieceColor.h" 

struct SavedSquare {
	bool hasPiece; //if set to false, every other param is ignored
	PieceColor color;
	bool king;

	template <class Archive> //serialization method, courtesy of the cereal library
	void serialize(Archive& ar) {
		ar(hasPiece, color, king);
	}
};