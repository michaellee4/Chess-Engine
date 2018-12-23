#ifndef IO_H
#define IO_H

#include "board.h"
#include "movemaker.h"	
#include "move.h"
#include "movelist.h"
#include "utils.h"
#include <string>
namespace IOHandler
{
	void printBoard(const Board& pos);
	void printBitBoard(const uint64_t);
	void printMoveList(const MoveList& list);
	Move parseMove(std::string input, Board& pos);
};

#endif
