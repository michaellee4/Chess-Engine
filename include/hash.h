#ifndef HASH_H
#define HASH_H
#include "board.h"

namespace Hash
{
	extern std::vector<std::vector<uint64_t>> PieceKeys;
	extern uint64_t SideKey;
	extern std::vector<uint64_t> CastleKeys;

	// generates a positions hash key
	uint64_t generatePosKey(const Board& pos);

	// Used in Make/Take as macros to update position key
	inline void hashPce(uint32_t pce, uint32_t sq, Board& pos)
	{
		pos.pos_key ^= (PieceKeys[(pce)][(sq)]);
	}
	inline void hashCa(Board& pos)
	{
		pos.pos_key ^= (CastleKeys[(pos.castle_perm)]);
	}
	inline void hashSide(Board& pos)
	{
		pos.pos_key ^= (SideKey);
	}
	inline void hashEP(Board& pos)
	{
		pos.pos_key ^= (PieceKeys[EMPTY][(pos.en_pas)]);
	}
};

#endif