#include "defs.h"
#include "hash.h"
#include "utils.h"
#include "board.h"

U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16];

U64 GeneratePosKey(const Board& pos)
{
	U64 hash = 0;
	for(int sq = 0; sq < BRD_SQ_NUM; sq ++)
	{
		int piece = pos.pieces[sq];

		//is actually a piece
		if(piece != NO_SQ && piece != EMPTY)
		{
			hash ^= PieceKeys[piece][sq];
		}
	}
	if(pos.side_to_move == WHITE)
	{
		hash ^= SideKey;
	}
	if(pos.en_pas != NO_SQ)
	{
		hash ^= PieceKeys[EMPTY][pos.en_pas];
	}

	hash ^= CastleKeys[pos.castle_perm];

	return hash;
}