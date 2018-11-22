#ifndef PERFT_H
#define PERFT_H

#include "board.h"
#include "movelist.h"
#include "movemaker.h"
#include "move.h"
class PerftTester
{

private:
	long leafNodes;
	void Perft(int depth, Board& pos);
public:
	void PerftTest(int depth, Board& pos);
};


#endif