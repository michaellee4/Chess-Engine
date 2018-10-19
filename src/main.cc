#include "defs.h"
#include <iostream>
#include <iomanip>
#include "bitboard.h"
#include "utils.h"
#include "init.h"
#include "hash.h"
#include "board.h"
#include <unordered_set>
using namespace std;

int main()
{
	InitAll();
	Board b;
	b.ParseFEN("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq a6 0 1");
	b.PrintBoard();
	return 0;
}