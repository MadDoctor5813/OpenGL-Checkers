#pragma once

struct BoardPos {
	int row;
	int col;

	bool operator==(BoardPos& rhs) {
		return (rhs.row == row && rhs.col == col);
	}

	bool operator!=(BoardPos& rhs) {
		return !(rhs.row == row && rhs.col == col);
	}
};