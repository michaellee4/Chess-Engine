/**
*	@file bitboard.cc
*	@brief Contains definitions of functions declared in bitboard.h.
*	@author Michael Lee
*	@date 1/9/2019
*/
#include "bitboard.h"
#include "constants.h"
#include "utils.h"
#include <cstdio>

/**
 * Sets the highest order bit to 0
 * Returns the value after the operations
 */
int BB::popBit(uint64_t& bb) noexcept
{
  uint64_t b = bb ^ (bb - 1);
  auto fold = static_cast<unsigned>((b & 0xffffffff) ^ (b >> 32));
  bb &= (bb - 1);
  return BB::BitTable[(fold * 0x783a9b23) >> 26];
}

/**
 * Returns the number of 1's in the bitboard
 */
int BB::countBits(uint64_t b) noexcept
{
  uint32_t r;
  for(r = 0; b; r++, b &= b - 1);
  return r;
}

/**
 * Sets the bit at index to 1
 */
void BB::setBit(uint64_t& bb, int index) noexcept
{
	bb |= BB::SetMask[index];
}

/**
 * Sets the bit at index to 0
 */
void BB::clearBit(uint64_t& bb, int index) noexcept
{
	bb &= BB::ClearMask[index];
}
