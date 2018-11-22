#ifndef HASH_H
#define HASH_H
#include "board.h"

namespace Hash
{
	U64 GeneratePosKey(const Board& pos);
	inline void HashPce(int pce, int sq, Board& pos)
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