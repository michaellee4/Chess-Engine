#include "utils.h"
#include "defs.h"
#include <random>
#include <sstream>
#include <string>
#include <sstream>
#include <algorithm>
//return the 120 sq value of a given file and rank
int FileRankToSq(int file, int rank)
{
	return 21 + file + rank * 10;
}

bool IsPiece(int piece)
{
	return (piece != OFFBOARD && piece != EMPTY && piece != NO_SQ);
}

std::string SqToString(const int sq)
{
	std::ostringstream stream;
	char file = 'a' + FileBrd[sq];
	char rank = '1' + RankBrd[sq];
	stream<<file<<rank;
	return stream.str();
}
 
//https://stackoverflow.com/questions/37396278/how-to-generate-very-large-random-number-in-c
uint64_t RandU64() 
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
	
	printf("\n\nSquares attacked by:%c\n",BoardChar::SideChar[side]);
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

void StringToLower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}