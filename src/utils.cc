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

std::string SqToString(const int sq)
{
	std::ostringstream stream;
	char file = 'a' + FileBrd[sq];
	char rank = '1' + RankBrd[sq];
	stream<<file<<rank;
	return stream.str();
}