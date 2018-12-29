#ifndef HASH_H
#define HASH_H
#include "board.h"
#include "defs.h"
#include <array>
namespace Hash
{
	extern std::array<std::array<uint64_t, kBoardArraySize>, kNumPceTypes> PieceKeys;
	extern uint64_t SideKey;
	extern std::array<uint64_t, 16> CastleKeys;

	// generates a positions hash key
	uint64_t generatePosKey(const Board& pos);

	// Used in Make/Take as macros to update position key
	inline void hashPce(uint32_t pce, uint32_t sq, Board& pos) noexcept
	{
		pos.pos_key ^= (PieceKeys[(pce)][(sq)]);
	}
	inline void hashCa(Board& pos) noexcept
	{
		pos.pos_key ^= (CastleKeys[(pos.castle_perm)]);
	}
	inline void hashSide(Board& pos) noexcept
	{
		pos.pos_key ^= (SideKey);
	}
	inline void hashEP(Board& pos) noexcept
	{
		pos.pos_key ^= (PieceKeys[EMPTY][(pos.en_pas)]);
	}
}

#endif