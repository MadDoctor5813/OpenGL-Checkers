#include "Board.h"


Board::Board() : boardData(BOARD_SIZE, std::vector<Piece *>(BOARD_SIZE, nullptr)) {
}


Board::~Board() {
}
