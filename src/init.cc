#include "defs.h"

int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

int FileRankToSq(int file, int rank)
{
	return 21 + file + rank * 10;
}

// creates 2 arrays to map 64 <-> 120 board square representations
void InitSq120ToSq64()
{
	int sq64 = 0;

	for(int index = 0; index < BRD_SQ_NUM; index++)
	{
		// use 65 as invalid value
		Sq120ToSq64[index] = 65;
	}

	for(int index = 0; index < 64; index++)
	{
		Sq64ToSq120[index] = 65;
	}

	for(int rank = RANK_1; rank <= RANK_8; rank++)
	{
		for(int file = FILE_A; file <= FILE_H; file++)
		{
			int sq = FileRankToSq(file, rank);
			Sq64ToSq120[sq64] = sq;
			Sq120ToSq64[sq] = sq64;
			sq64++;
		}
	}
}



void InitAll()
{
	InitSq120ToSq64();
}