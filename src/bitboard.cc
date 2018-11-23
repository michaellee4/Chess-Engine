#include "defs.h"
#include <cstdio>
#include "bitboard.h"
#include "utils.h"


extern uint64_t SetMask[64];
extern uint64_t ClearMask[64];

// removes the lowest order bit of an integer and returns the index
int BB::PopBit(uint64_t& bb) {
  uint64_t b = bb ^ (bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  bb &= (bb - 1);
  return BBmask::BitTable[(fold * 0x783a9b23) >> 26];
}

// counts the number of 1 bits
int BB::CountBits(uint64_t b) {
  int r;
  for(r = 0; b; r++, b &= b - 1);
  return r;
}

void BB::SetBit(uint64_t& bb, int index)
{
	bb |= SetMask[index];
}

void BB::ClearBit(uint64_t& bb, int index)
{
	bb &= ClearMask[index];
}

void BB::PrintBitBoard(uint64_t bb)
{
	for (int rank = RANK_8; rank >=RANK_1; --rank)
	{
		for(int file = FILE_A; file <= FILE_H; ++file)
		{
			int sq = FileRankToSq(file, rank);
			int sq64 = Sq120ToSq64[sq];

			printf("%c", ((1ULL << sq64) & bb) ? 'X' : '-' );
		}
		printf("\n");
	}
	printf("\n\n");
}