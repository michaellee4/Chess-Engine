#ifndef HASH_H
#define HASH_H
#include "board.h"

namespace Hash
{
	uint64_t GeneratePosKey(const Board& pos);
	inline void HashPce(uint32_t pce, uint32_t sq, Board& pos)
	{
		pos.pos_key ^= (PieceKeys[(pce)][(sq)]);
	}
	inline void HashCa(Board& pos)
	{
		pos.pos_key ^= (CastleKeys[(pos.castle_perm)]);
	}
	inline void HashSide(Board& pos)
	{
		pos.pos_key ^= (SideKey);
	}
	inline void HashEP(Board& pos)
	{
		pos.pos_key ^= (PieceKeys[EMPTY][(pos.en_pas)]);
	}
};

#endif