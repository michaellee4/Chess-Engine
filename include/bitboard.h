#ifndef BITBOARD_H
#define BITBOARD_H

#include "defs.h"

/**
 * This namespace provides several methods
 * relating to the manipulation of bitboards
 * most notably the pawn bitboards.
 */
namespace BB
{
	/**
	 * Magic numbers used for pop/set bit in bitboard
	 */
	constexpr std::array<int32_t, kChessboardSize> BitTable = {
	  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
	  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
	  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
	  58, 20, 37, 17, 36, 8
	};

	/**
	 * bit masks used to set/clear bits on a bitboard
	 */
	extern std::array<uint64_t, kChessboardSize> SetMask;
	extern std::array<uint64_t, kChessboardSize> ClearMask;
	
	/**
	 * Input: 64 bit bitboard
	 * Output: Resulting value after operation
	 * Operation: sets the highest order 1 bit to 0
	 */
	int popBit(uint64_t&) noexcept;

	/**
	 * Input: 64 bit bitboard
	 * Output: Number of 1's in provided bitboard
	 * Operation: None
	 */
	int countBits(uint64_t bb)noexcept;

	/**
	 * Input: 64 bit bitboard, index
	 * Output: None
	 * Operation: sets the bit at index to 1
	 */
	void setBit(uint64_t& bb, int index)noexcept;

	/**
	 * Input: 64 bit bitboard, index
	 * Output: None
	 * Operation: sets the bit at index to 0
	 */
	void clearBit(uint64_t& bb, int index)noexcept;
}


#endif