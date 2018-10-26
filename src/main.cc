#include "defs.h"
#include <iostream>
#include <iomanip>
#include "bitboard.h"
#include "utils.h"
#include "init.h"
#include "hash.h"
#include "board.h"
#include <unordered_set>

#define TOUGHFEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

using namespace std;


int main()
{
		InitAll();
	Board b;
	b.ParseFEN(TOUGHFEN);

	b.PrintBoard();
	PrintBitBoard(b.pawns[WHITE]);
	PrintBitBoard(b.pawns[BLACK]);
	PrintBitBoard(b.pawns[BOTH]);

	printf("***\n");
	return 0;
}