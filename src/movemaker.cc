#include "movemaker.h"
#include "defs.h"
#include "bitboard.h"
#include "debug.h"

void ClearPiece(const int sq, Board& pos)
{
	int pce = pos.pieces[sq];
	int col = PieceCol[pce];
	
	HASH_PCE(pce, sq);

	pos.pieces[sq] = EMPTY;
	pos.material[col] -= PieceVal[pce];
	if (PieceBig[pce])
	{
		pos.big_pce[col]--;
		if (PieceMaj[pce])
		{
			pos.maj_pce[col]--;
		}
		else
		{
			pos.min_pce[col]--;
		}
	}
	else
	{
		ClearBit(pos.pawns[col], Sq120ToSq64[sq]);
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

void AddPiece(const int sq, Board& pos, const int pce)
{
	int col = PieceCol[pce];
	HASH_PCE(pce, sq);
	pos.pieces[sq] = pce;

	if(PieceBig[pce])
	{
		pos.big_pce[col]++;
		if(PieceMaj[pce])
		{
			pos.maj_pce[col]++;
		}
		else
		{
			pos.min_pce[col]++;
		}
	}
	else
	{
		SetBit(pos.pawns[col], Sq120ToSq64[sq]);
		SetBit(pos.pawns[BOTH], Sq120ToSq64[sq]);
	}
	
	pos.material[col]+=PieceVal[pce];
	pos.piece_list[pce][pos.piece_num[pce]++] = sq;
}

void MovePiece(const int src, const int dest, Board& pos)
{
	int pce = pos.pieces[src];
	int col = PieceCol[pce];

	HASH_PCE(pce, src);
	pos.pieces[src] = EMPTY;
	HASH_PCE(pce, dest);
	pos.pieces[dest] = pce;

	if(!PieceBig[pce])
	{
		ClearBit(pos.pawns[col], Sq120ToSq64[src]);
		ClearBit(pos.pawns[BOTH], Sq120ToSq64[src]);
		SetBit(pos.pawns[col], Sq120ToSq64[dest]);
		SetBit(pos.pawns[BOTH], Sq120ToSq64[dest]);
	}

	// ADD PIECE TO PIECE LIST
	int idx = 0;
	for (; idx < pos.piece_num[pce] && pos.piece_list[pce][idx] != src; idx++){}

	// should always find something
	ASSERT(idx != pos.piece_num[pce]);
	pos.piece_list[pce][idx] = dest;
	
}