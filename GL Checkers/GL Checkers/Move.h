#pragma once

struct Move {
	int oldRow;
	int oldCol;
	int newRow;
	int newCol;

	Move(int oldRow, int oldCol, int newRow, int newCol) : oldRow(oldRow), oldCol(oldCol), newRow(newRow), newCol(newCol) {}
};