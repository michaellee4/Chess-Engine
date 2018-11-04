#include "utils.h"
#include <random>
#include <sstream>
//return the 120 sq value of a given file and rank
int FileRankToSq(int file, int rank)
{
	return 21 + file + rank * 10;
}
 
//https://stackoverflow.com/questions/37396278/how-to-generate-very-large-random-number-in-c
U64 RandU64() 
{
	using namespace std;
	  /* Seed */
	random_device rd;

	/* Random number generator */
	default_random_engine generator(rd());

	/* Distribution on which to apply the generator */
	uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);
	return distribution(generator);
}


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