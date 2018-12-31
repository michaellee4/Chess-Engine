#include "defs.h"
#include "hash.h"
#include "utils.h"
#include "board.h"
uint64_t Hash::generatePosKey(const Board& pos)
{
	uint64_t hash = 0;
	for(uint32_t sq = 0; sq < kBoardArraySize; ++sq)
	{
		int piece = pos.pieces[sq];
		//is actually a piece
		if(piece != NO_SQ && piece != EMPTY && piece != OFFBOARD)
		{
			hash ^= Hash::PieceKeys[piece][sq];
		}
	}
	if(pos.side_to_move == WHITE)
	{
		hash ^= Hash::SideKey;
	}
	if(pos.en_pas != NO_SQ)
	{
		hash ^= Hash::PieceKeys[EMPTY][pos.en_pas];
	}
	hash ^= Hash::CastleKeys[pos.castle_perm];
	return hash;
}