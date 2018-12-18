#include "defs.h"
#include <iostream>
#include <iomanip>
#include "bitboard.h"
#include "utils.h"
#include "init.h"
#include "hash.h"
#include "board.h"
#include "movelist.h"
#include <unordered_set>
#include "stopwatch.h"
#include "movemaker.h"
#include <cstdio>
#include <bitset>
#include "perft.h"
#include "io.h"
#define PERFTFEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define pt "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

using namespace std;

int main()
{
	//Testing commig
	
	InitAll();
	Board b;
	PerftTester p;
	IOHandler::PrintBoard(b);
	/*
	b.ParseFEN("r3k2r/8/8/8/8/8/8/R3K1R1 b Qkq - 0 1");	
	ASSERT(CheckBoard(b));
	Stopwatch s;
	p.PerftTest(6, b);
	*/
	Stopwatch s;
	p.PerftTestAll(b);
	// cout << Stopwatch::getTimeInMilli() << endl;
	return 0;
}
