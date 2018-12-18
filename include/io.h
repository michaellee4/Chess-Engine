#ifndef IO_H
#define IO_H

#include "board.h"
#include "movemaker.h"	
#include "move.h"
#include "movelist.h"
#include "utils.h"

namespace IOHandler
{
	void PrintBoard(const Board& pos);
	void PrintBitBoard(const uint64_t);
	void PrintMoveList(const MoveList& list);
	static Move ParseMove;
};

#endif
