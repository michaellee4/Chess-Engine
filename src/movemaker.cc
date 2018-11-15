#include "movemaker.h"
#include "defs.h"
#include "bitboard.h"
#include "debug.h"
#include "utils.h"
#include "move.h"

#include<cstdio>

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
	ASSERT(IsPiece(pce));
	ASSERT(pos.SqOnBoard(sq));

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
    ASSERT(pos.SqOnBoard(src));
    ASSERT(pos.SqOnBoard(dest));

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

bool MakeMove(Board& pos, Move moveInfo)
{
	ASSERT(CheckBoard(pos));

	int from = moveInfo.From();
	int to = moveInfo.To();
	int side = pos.side_to_move;
	int move = moveInfo.move;

	ASSERT(pos.SqOnBoard(from));
	ASSERT(pos.SqOnBoard(to));
	ASSERT(pos.SqOnBoard(from));
	ASSERT(IsPiece(pos.pieces[from]))

	pos.history[pos.hist_ply].posKey = pos.pos_key;

	if(move & EP)
	{
		int offset = side == WHITE ? -10 : 10;
		ClearPiece(to + offset, pos);
	}
	else if (move & CA)
	{
		switch(to)
		{
			case C1:
				MovePiece(A1, D1, pos);
			break;
			case C8:
				MovePiece(A8, D8, pos);
			break;
			case G1:
				MovePiece(H1, F1, pos);
			break;
			case G8:
				MovePiece(H8, F8, pos);
			break;
			default: ASSERT(false); break;
		}
	}
	if(pos.en_pas != NO_SQ) HASH_EP;
	HASH_CA;

	pos.history[pos.hist_ply].move = move;
	pos.history[pos.hist_ply].fiftyMove = pos.fifty_move;
	pos.history[pos.hist_ply].enPas = pos.en_pas;
	pos.history[pos.hist_ply].castlePerm = pos.castle_perm;

	pos.castle_perm &= CastlePerm[from];
	pos.castle_perm &= CastlePerm[to];
	pos.en_pas = NO_SQ;

	HASH_CA;

	int captured = moveInfo.Captured();
	pos.fifty_move++;

	if(captured != EMPTY)
	{
		ASSERT(IsPiece(captured));
		ClearPiece(to, pos);
		pos.fifty_move = 0;
	}

	pos.hist_ply++;
	pos.ply++;

	if(PiecePawn[pos.pieces[from]])
	{
		pos.fifty_move = 0;
		if(move & PS)
		{
			int offset = side == WHITE ? 10 : -10;
			pos.en_pas = from + offset;
			ASSERT((side == WHITE && RankBrd[pos.en_pas] == RANK_3)||(side == BLACK && RankBrd[pos.en_pas] == RANK_6));
			HASH_EP;
		}
	}

	MovePiece(from , to , pos);

	int promotion = moveInfo.Promoted();
	if(promotion != EMPTY)
	{
		ASSERT(IsPiece(promotion) && !PiecePawn[promotion]);
		ClearPiece(to, pos);
		AddPiece(to, pos, promotion);
	}

	if(PieceKing[pos.pieces[to]])
	{
		pos.king_sq[pos.side_to_move] = to;
	}

	pos.side_to_move ^= 1;
	HASH_SIDE;
	ASSERT(CheckBoard(pos));

	if(pos.SqAttacked(pos.king_sq[side], !side))
	{
		TakeMove(pos);
		return false;
	}
	return true;
}

void TakeMove(Board& pos)
{
	ASSERT(CheckBoard(pos));

	pos.hist_ply--;
	pos.ply--;

	Move moveInfo = Move(pos.history[pos.hist_ply].move);
	int move = moveInfo.move;
	int from = moveInfo.From();
	int to = moveInfo.To();

	ASSERT(pos.SqOnBoard(from) && pos.SqOnBoard(to));

	if(pos.en_pas != NO_SQ) HASH_EP;
	HASH_CA;

	U_Move undo = pos.history[pos.hist_ply];
	pos.castle_perm = undo.castlePerm;
	pos.fifty_move = undo.fiftyMove;
	pos.en_pas = undo.enPas;

    if(pos.en_pas != NO_SQ) HASH_EP;
    HASH_CA;

	pos.side_to_move ^= 1;
	HASH_SIDE;

	if(move & EP)
	{
		int offset = pos.side_to_move == WHITE ? -10 : 10;
		int pce = pos.side_to_move == WHITE ? bP: wP;
		AddPiece(to + offset, pos, pce);
	}
	else if (move & CA)
	{
		switch(to)
		{
			case C1:
				MovePiece(D1, A1, pos);
			break;
			case C8:
				MovePiece(D8, A8, pos);
			break;
			case G1:
				MovePiece(F1, H1, pos);
			break;
			case G8:
				MovePiece(F8, H8, pos);
			break;
			default: ASSERT(false); break;
		}
	}
	MovePiece(to, from, pos);
	ASSERT(IsPiece(pos.pieces[from]));
	if (PieceKing[pos.pieces[from]])
	{
		pos.king_sq[pos.side_to_move] = from;
	}

	int captured = moveInfo.Captured();
	if(captured != EMPTY)
	{
		ASSERT(IsPiece(captured));
		AddPiece(to, pos, captured);
	}

	int promotion = moveInfo.Promoted();
	if(promotion != EMPTY)
	{
		ASSERT(IsPiece(promotion) && !PiecePawn[promotion]);
		ClearPiece(from, pos);
		AddPiece(from, pos, (PieceCol[promotion] == WHITE ? wP : bP));
	}
	ASSERT(CheckBoard(pos));
}