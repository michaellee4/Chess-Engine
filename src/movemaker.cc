#include "movemaker.h"
#include "defs.h"
#include "bitboard.h"
#include "debug.h"
#include "utils.h"
#include "move.h"
#include "hash.h"
#include<cstdio>
#include <algorithm>

void MM::clearPiece(const uint32_t sq, Board& pos) noexcept
{
	int pce = pos.pieces[sq];
	int col = PieceInfo::PieceCol[pce];
	
	Hash::hashPce(pce, sq, pos);

	pos.pieces[sq] = EMPTY;
	pos.material[col] -= PieceInfo::PieceVal[pce];
	if (PieceInfo::PieceBig[pce])
	{
		--pos.big_pce[col];
		if (PieceInfo::PieceMaj[pce])
		{
			--pos.maj_pce[col];
		}
		else
		{
			--pos.min_pce[col];
		}
	}
	else
	{
		BB::clearBit(pos.pawns[col], BoardUtils::Sq120ToSq64[sq]);
		BB::clearBit(pos.pawns[BOTH], BoardUtils::Sq120ToSq64[sq]);
	}
	pos.piece_list[pce].erase(std::remove(pos.piece_list[pce].begin(), pos.piece_list[pce].end(), sq), pos.piece_list[pce].end());
}

void MM::addPiece(const uint32_t sq, Board& pos, const uint32_t pce) noexcept
{
	ASSERT(isPiece(pce));
	ASSERT(pos.sqOnBoard(sq));

	int col = PieceInfo::PieceCol[pce];
	Hash::hashPce(pce, sq, pos);
	pos.pieces[sq] = pce;

	if(PieceInfo::PieceBig[pce])
	{
		++pos.big_pce[col];
		if(PieceInfo::PieceMaj[pce])
		{
			++pos.maj_pce[col];
		}
		else
		{
			++pos.min_pce[col];
		}
	}
	else
	{
		BB::setBit(pos.pawns[col], BoardUtils::Sq120ToSq64[sq]);
		BB::setBit(pos.pawns[BOTH], BoardUtils::Sq120ToSq64[sq]);
	}
	
	pos.material[col]+=PieceInfo::PieceVal[pce];

	pos.piece_list[pce].push_back(sq);
}

void MM::movePiece(const uint32_t src, const uint32_t dest, Board& pos) noexcept
{
    ASSERT(pos.sqOnBoard(src));
    ASSERT(pos.sqOnBoard(dest));

	int pce = pos.pieces[src];
	int col = PieceInfo::PieceCol[pce];

	Hash::hashPce(pce, src, pos);
	pos.pieces[src] = EMPTY;
	Hash::hashPce(pce, dest, pos);
	pos.pieces[dest] = pce;

	if(!PieceInfo::PieceBig[pce])
	{
		BB::clearBit(pos.pawns[col], BoardUtils::Sq120ToSq64[src]);
		BB::clearBit(pos.pawns[BOTH], BoardUtils::Sq120ToSq64[src]);
		BB::setBit(pos.pawns[col], BoardUtils::Sq120ToSq64[dest]);
		BB::setBit(pos.pawns[BOTH], BoardUtils::Sq120ToSq64[dest]);
	}
	//find and replace the old sq with the dest sq
	*std::find(pos.piece_list[pce].begin(), pos.piece_list[pce].end(), src)  = dest;	
}

bool MM::makeMove(Board& pos, const Move& moveInfo) noexcept
{
	if(moveInfo == NOMOVE)
		return false;
	ASSERT(checkBoard(pos));

	int from = moveInfo.from();
	int to = moveInfo.to();
	int side = pos.side_to_move;
	int move = moveInfo.move;

	ASSERT(pos.sqOnBoard(from));
	ASSERT(pos.sqOnBoard(to));
	ASSERT(pos.sqOnBoard(from));
	ASSERT(isPiece(pos.pieces[from]))

	pos.history[pos.hist_ply].pos_key = pos.pos_key;

	if(move & EP)
	{
		int offset = Attack::PnMoves[side];
		MM::clearPiece(to + offset, pos);
	}
	else if (move & CA)
	{
		switch(to)
		{
			case C1:
				MM::movePiece(A1, D1, pos);
			break;
			case C8:
				MM::movePiece(A8, D8, pos);
			break;
			case G1:
				MM::movePiece(H1, F1, pos);
			break;
			case G8:
				MM::movePiece(H8, F8, pos);
			break;
			default: ASSERT(false); break;
		}
	}
	if(pos.en_pas != NO_SQ) Hash::hashEP(pos);
	Hash::hashCa(pos);

	pos.history[pos.hist_ply] = U_Move(move, pos);

	pos.castle_perm &= CastlePerm[from] & CastlePerm[to];
	pos.en_pas = NO_SQ;

	Hash::hashCa(pos);

	int captured = moveInfo.captured();
	++pos.fifty_move;

	if(captured != EMPTY)
	{
		ASSERT(isPiece(captured));
		MM::clearPiece(to, pos);
		pos.fifty_move = 0;
	}

	++pos.hist_ply;
	++pos.ply;

	if(PieceInfo::PiecePawn[pos.pieces[from]])
	{
		pos.fifty_move = 0;
		if(move & PS)
		{
			int offset = Attack::PnMoves[!side];
			pos.en_pas = from + offset;
			ASSERT((side == WHITE && BoardUtils::RankBrd[pos.en_pas] == RANK_3)||(side == BLACK && BoardUtils::RankBrd[pos.en_pas] == RANK_6));
			Hash::hashEP(pos);
		}
	}

	MM::movePiece(from , to , pos);

	int promotion = moveInfo.promoted();
	if(promotion != EMPTY)
	{
		ASSERT(isPiece(promotion) && !PieceInfo::PiecePawn[promotion]);
		MM::clearPiece(to, pos);
		MM::addPiece(to, pos, promotion);
	}

	if(PieceInfo::PieceKing[pos.pieces[to]])
	{
		pos.king_sq[pos.side_to_move] = to;
	}

	pos.side_to_move ^= 1;
	Hash::hashSide(pos);
	ASSERT(checkBoard(pos));

	if(pos.sqAttacked(pos.king_sq[side], !side))
	{
		MM::takeMove(pos);
		return false;
	}
	return true;
}

void MM::takeMove(Board& pos) noexcept
{
	ASSERT(checkBoard(pos));

	--pos.hist_ply;
	--pos.ply;

	Move moveInfo = Move(pos.history[pos.hist_ply].move);
	int move = moveInfo.move;
	int from = moveInfo.from();
	int to = moveInfo.to();

	ASSERT(pos.sqOnBoard(from) && pos.sqOnBoard(to));

	if(pos.en_pas != NO_SQ) Hash::hashEP(pos);
	Hash::hashCa(pos);

	U_Move undo = pos.history[pos.hist_ply];
	pos.castle_perm = undo.castlePerm;
	pos.fifty_move = undo.fiftyMove;
	pos.en_pas = undo.enPas;

    if(pos.en_pas != NO_SQ) Hash::hashEP(pos);
    Hash::hashCa(pos);

	pos.side_to_move ^= 1;
	Hash::hashSide(pos);

	if(move & EP)
	{
		int offset = Attack::PnMoves[pos.side_to_move];
		int pce = pos.side_to_move == WHITE ? bP: wP;
		MM::addPiece(to + offset, pos, pce);
	}
	else if (move & CA)
	{
		switch(to)
		{
			case C1:
				MM::movePiece(D1, A1, pos);
			break;
			case C8:
				MM::movePiece(D8, A8, pos);
			break;
			case G1:
				MM::movePiece(F1, H1, pos);
			break;
			case G8:
				MM::movePiece(F8, H8, pos);
			break;
			default: ASSERT(false); break;
		}
	}
	MM::movePiece(to, from, pos);
	ASSERT(isPiece(pos.pieces[from]));
	if (PieceInfo::PieceKing[pos.pieces[from]])
	{
		pos.king_sq[pos.side_to_move] = from;
	}

	int captured = moveInfo.captured();
	if(captured != EMPTY)
	{
		ASSERT(isPiece(captured));
		MM::addPiece(to, pos, captured);
	}

	int promotion = moveInfo.promoted();
	if(promotion != EMPTY)
	{
		ASSERT(isPiece(promotion) && !PieceInfo::PiecePawn[promotion]);
		MM::clearPiece(from, pos);
		MM::addPiece(from, pos, (PieceInfo::PieceCol[promotion] == WHITE ? wP : bP));
	}
	ASSERT(checkBoard(pos));
}