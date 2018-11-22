#ifndef PERFT_H
#define PERFT_H

#include "board.h"
#include "movelist.h"
#include "movemaker.h"
#include "move.h"
#include <string>
#include <sstream>

class PerftTester
{
private:
	const int depth_limit = 6;
	long testArr[6 + 1];
	long leafNodes;
	void Perft(int depth, Board& pos);
public:
	void PerftTest(int depth, Board& pos);
	void PerftTestAll(Board& pos);
};


#endif