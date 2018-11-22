#include "defs.h"
#include <cstdio>
#include "bitboard.h"
#include "utils.h"


extern U64 SetMask[64];
extern U64 ClearMask[64];

// removes the lowest order bit of an integer and returns the index
int BB::PopBit(U64& bb) {
  U64 b = bb ^ (bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  bb &= (bb - 1);
  return BBmask::BitTable[(fold * 0x783a9b23) >> 26];
}

// counts the number of 1 bits
int BB::CountBits(U64 b) {
  int r;
  for(r = 0; b; r++, b &= b - 1);
  return r;
}

void BB::SetBit(U64& bb, int index)
{
	bb |= SetMask[index];
}

void BB::ClearBit(U64& bb, int index)
{
	bb &= ClearMask[index];
}

void BB::PrintBitBoard(U64 bb)
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