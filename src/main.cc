#include "defs.h"
#include <iostream>
#include <iomanip>
#include "bitboard.h"
#include "utils.h"
#include "init.h"
#include "hash.h"
#include "board.h"
#include <unordered_set>

#define FEN1 "8/3q1p2/8/5P2/4Q3/8/8/8 w - - 0 2 "
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define testFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -"
using namespace std;


void ShowSqAtBySide(const int side,Board& pos) {
		
	int rank = 0;
	int file = 0;
	int sq = 0;
	
	printf("\n\nSquares attacked by:%c\n",SideChar[side]);
	for(rank = RANK_8; rank >= RANK_1; --rank) {
		for(file = FILE_A; file <= FILE_H; ++file) {
			sq = FileRankToSq(file,rank);
			int numAtk = pos.SqAttacked(sq, side);
			printf("%i",numAtk );
				
		}
		printf("\n");
	}  
    printf("\n\n");

}


int main()
{
	InitAll();
	Board b;
	b.ParseFEN(testFEN);	
	b.PrintBoard();	
	ASSERT(CheckBoard(b));

	Move test;

	test.move = 0;
	test.move |= A2;
	test.move |= (H6 <<7);
	test.move |= (wR <<14);
	test.move |= (wK << 20);

	printf("SQ: %s\n",Board::SqToString(A2).c_str() );
	printf("SQ: %s\n",b.SqToString(H6).c_str() );
	printf("Move: %s \n", test.ToString().c_str());
	return 0;
}