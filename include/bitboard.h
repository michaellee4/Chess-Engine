/**
*	@file bitboard.h
*	@brief Contains declarations of functions that manipulate bitboards.
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef BITBOARD_H
#define BITBOARD_H

#include "constants.h"

namespace BB
{
	/**
	 * Magic numbers used for pop/set bit in bitboard
	 */
	constexpr std::array<int32_t, kChessboardSize> BitTable 
	{
	  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
	  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
	  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
	  58, 20, 37, 17, 36, 8
	};
	extern std::array<uint64_t, kChessboardSize> SetMask;
	extern std::array<uint64_t, kChessboardSize> ClearMask;
	
/**
	@brief Sets the highest order 1 bit to 0.
	@param bb The desired bitboard
	@return The index of the bit that was flipped
 */
	int popBit(uint64_t& bb) noexcept;

/**
	@brief Counts the number of 1's in the bitboard.
	@param bb The desired bitboard
	@return The number of 1's in the bitboard.
 */
	int countBits(uint64_t bb)noexcept;

/**
	@brief Sets the bit at index to 1.
	@param bb The desired bitboard
	@param index The index to set to 1
	@return None.
 */
	void setBit(uint64_t& bb, int index)noexcept;


/**
	@brief Sets the bit at index to 0.
	@param bb The desired bitboard.
	@param index The index to set to 0.
	@return None.
 */
	void clearBit(uint64_t& bb, int index)noexcept;
}


#endif