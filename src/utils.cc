#include "utils.h"

//return the 120 sq value of a given file and rank
int FileRankToSq(int file, int rank)
{
	return 21 + file + rank * 10;
}

