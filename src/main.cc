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
#define FEN1 "8/3q1p2/8/5P2/4Q3/8/8/8 w - - 0 2 "
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define testFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -"
#define PAWNMOVESW "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define PAWNMOVESB "rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b KQkq e3 0 1"
#define KNIGHTSKINGS "5k2/1n6/4n3/6N1/8/3N4/8/5K2 w - - 0 1"
#define ROOKS "6k1/8/5r2/8/1nR5/5N2/8/6K1 w - - 0 1"
#define QUEENS "6k1/8/4nq2/8/1nQ5/5N2/1N6/6K1 b - - 0 1 "
#define BISHOPS "6k1/1b6/4n3/8/1n4B1/1B3N2/1N6/2b3K1 b - - 0 1 "
#define CASTLE1 "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"
#define CASTLE2 "3rk2r/8/8/8/8/8/6p1/R3K2R b KQk - 0 1"
#define GENALLMOVE "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

#define PERFTFEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define pt "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

using namespace std;

int main()
{
	//Testing commig
	
	InitAll();
	Board b;
	PerftTester p;

	/*
	b.ParseFEN("r3k2r/8/8/8/8/8/8/R3K1R1 b Qkq - 0 1");	
	ASSERT(CheckBoard(b));
	Stopwatch s;
	p.PerftTest(6, b);
	*/
	p.PerftTestAll(b);
	return 0;
}
