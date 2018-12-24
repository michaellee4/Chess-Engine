#ifndef BITBOARD_H
#define BITBOARD_H

#include "defs.h"

// General namespace used for manipulating bitboards
namespace BB
{
	// Magic numbers used for pop/set bit in bitboard
	const std::vector<int> BitTable = {
	  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
	  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
	  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
	  58, 20, 37, 17, 36, 8
	};

	extern std::vector<uint64_t> SetMask;
	extern std::vector<uint64_t> ClearMask;
	
	// removes the lowest order bit of an integer and returns the index
	int popBit(uint64_t&);
	// counts the number of 1 bits
	int countBits(uint64_t);

	// void printBitBoard(uint64_t);
	// sets the given bit to 1
	void setBit(uint64_t&, int);
	// sets the given bit to 0
	void clearBit(uint64_t&, int);
}


#endif