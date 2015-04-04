#pragma once

#include <memory>

struct Square {
	std::unique_ptr<PieceInfo> piece;
};