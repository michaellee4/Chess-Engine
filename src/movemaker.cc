#include "movemaker.h"
#include "board.h"
#include "defs.h"
#include "bitboard.h"
#include "debug.h"

void ClearPiece(const int sq, Board& pos)
{
	int pce = pos.pieces[sq];
	int pceCol = PieceCol[pce];
	
	HASH_PCE(pce, sq);

	pos.pieces[sq] = EMPTY;
	pos.material[pceCol] -= PieceVal[pce];
	if (PieceBig[pce])
	{
		pos.big_pce[pceCol]--;
		if (PieceMaj[pce])
		{
			pos.maj_pce[pceCol]--;
		}
		else
		{
			pos.min_pce[pceCol]--;
		}
	}
	else
	{
		ClearBit(pos.pawns[pceCol], Sq120ToSq64[sq]);
		ClearBit(pos.pawns[BOTH], Sq120ToSq64[sq]);
	}

	// REMOVE PIECE FROM PIECE LIST
	int idx = 0;
	for (; idx < pos.piece_num[pce] && pos.piece_list[pce][idx] != sq; idx++){}

	// should always find something
	ASSERT(idx != pos.piece_num[pce])
	
	// swap out the value
	pos.piece_num[pce]--;
	pos.piece_list[pce][idx] = pos.piece_list[pce][pos.piece_num[pce]];
}