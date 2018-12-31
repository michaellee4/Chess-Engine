#ifndef POLYGLOT_H
#define POLYGLOT_H
#include "defs.h"

namespace Polyglot
{
	constexpr std::array<int32_t, 13> polyPiece { -1, 1, 3, 5, 7, 9, 11, 0, 2, 4, 6, 8, 10};
	bool enPasPossible(const Board& pos);
	uint64_t polyKeyFromBoard(const Board& pos);
}

#endif