#include "defs.h"
#include <cstdio>

void PrintBitBoard(U64 bb)
{
	for (int rank = RANK_8; rank >=RANK_1; rank--)
	{
		for(int file = FILE_A; file <= FILE_H; file++)
		{
			int sq = FileRankToSq(file, rank);
			int sq64 = Sq120ToSq64[sq];

			printf("%c", ((1ULL << sq64) & bb) ? 'X' : '-' );
		}
		printf("\n");
	}
	printf("\n\n");
}