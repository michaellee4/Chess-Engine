#ifndef BITBOARD_H
#define BITBOARD_H

#include "defs.h"

namespace BBmask
{
	const std::vector<int> BitTable = {
	  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
	  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
	  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
	  58, 20, 37, 17, 36, 8
	};
}

class BB
{
public:
	static int PopBit(uint64_t&);
	static int CountBits(uint64_t);
	static void PrintBitBoard(uint64_t);
	static void SetBit(uint64_t&, int);
	static void ClearBit(uint64_t&, int);
};

#endif