#include "defs.h"
#include "hash.h"
#include "utils.h"
#include "board.h"

uint64_t PieceKeys[13][120];
uint64_t SideKey;
uint64_t CastleKeys[16];

uint64_t Hash::generatePosKey(const Board& pos)
{
	uint64_t hash = 0;
	for(uint32_t sq = 0; sq < BRD_SQ_NUM; ++sq)
	{
		int piece = pos.pieces[sq];

		//is actually a piece
		if(piece != NO_SQ && piece != EMPTY)
		{
			ASSERT(piece>=wP && piece<=bK);
			hash ^= PieceKeys[piece][sq];
		}
	}
	if(pos.side_to_move == WHITE)
	{
		hash ^= SideKey;
	}
	if(pos.en_pas != NO_SQ)
	{
		ASSERT(pos.en_pas>=0 && pos.en_pas<BRD_SQ_NUM);
		hash ^= PieceKeys[EMPTY][pos.en_pas];
	}
	ASSERT(pos.castle_perm>=0 && pos.castle_perm<=15);
	hash ^= CastleKeys[pos.castle_perm];

	return hash;
}