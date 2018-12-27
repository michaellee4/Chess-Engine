#include "defs.h"
#include <cstdio>
#include "bitboard.h"
#include "utils.h"

int BB::popBit(uint64_t& bb) noexcept
{
  uint64_t b = bb ^ (bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  bb &= (bb - 1);
  return BB::BitTable[(fold * 0x783a9b23) >> 26];
}

int BB::countBits(uint64_t b) noexcept
{
  uint32_t r;
  for(r = 0; b; r++, b &= b - 1);
  return r;
}

void BB::setBit(uint64_t& bb, int index) noexcept
{
	bb |= BB::SetMask[index];
}

void BB::clearBit(uint64_t& bb, int index) noexcept
{
	bb &= BB::ClearMask[index];
}

