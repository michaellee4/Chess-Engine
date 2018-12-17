#ifndef PERFT_H
#define PERFT_H

#include "board.h"
#include "movelist.h"
#include "movemaker.h"
#include "move.h"
#include <string>
#include <sstream>

// Generate and counts all legal moves to a given depths.
// Correct values given in the perft.epd file in root dir
class PerftTester
{
private:
	const uint32_t depth_limit = 6;
	long testArr[6 + 1];
	long leafNodes;
	void Perft(uint32_t depth, Board& pos);
public:
	int PerftTest(uint32_t depth, Board& pos, bool print);
	void PerftTestAll(Board& pos);
};


#endif
