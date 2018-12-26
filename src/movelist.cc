#include "movelist.h"
#include <bitset>
#include <iostream>
#include <utility>
MoveList::MoveList()
{
	moves.reserve(MAX_MOVES_PER_POSITION);
}

MoveList::MoveList(const MoveList& o) : moves(o.moves) {}

MoveList::MoveList(MoveList&& o) noexcept : moves(std::move(o.moves)) {}


void MoveList::addQuietMove(const Board& pos, Move&& move)
{
	(void)pos;
	this->moves.emplace_back(move);
}
void MoveList::addCaptureMove(const Board& pos, Move&& move)
{
	move.score = MvvLva::MvvLvaScore[move.captured()][pos.pieces[move.from()]];
	this->moves.emplace_back(move);
}
void MoveList::addEnPasMove(const Board& pos, Move&& move)
{
	(void) pos;
	move.score = 105;
	this->moves.emplace_back(move);
}

void MoveList::addPawnMove(const Board& pos, uint32_t from, uint32_t to, uint32_t side)
{
	if(side == WHITE)
	{
		if(BoardUtils::RankBrd[from] == RANK_7)
		{
			this->addQuietMove(pos, Move(from,to,EMPTY,wQ,0));
			this->addQuietMove(pos, Move(from,to,EMPTY,wR,0));
			this->addQuietMove(pos, Move(from,to,EMPTY,wB,0));
			this->addQuietMove(pos, Move(from,to,EMPTY,wN,0));
		}
		else
		{
			this->addQuietMove(pos, Move(from,to,EMPTY,EMPTY,0));
		}	
	}
	else
	{
		if(BoardUtils::RankBrd[from] == RANK_2)
		{
			this->addQuietMove(pos, Move(from,to,EMPTY,bQ,0));
			this->addQuietMove(pos, Move(from,to,EMPTY,bR,0));
			this->addQuietMove(pos, Move(from,to,EMPTY,bB,0));
			this->addQuietMove(pos, Move(from,to,EMPTY,bN,0));
		}
		else
		{
			this->addQuietMove(pos, Move(from,to,EMPTY,EMPTY,0));
		}	
	}

}
void MoveList::addPawnCaptureMove(const Board& pos, uint32_t from, uint32_t to, uint32_t cap, uint32_t side)
{
	if(side == WHITE)
	{
		if(BoardUtils::RankBrd[from] == RANK_7)
		{
			this->addCaptureMove(pos, Move(from,to,cap,wQ,0));
			this->addCaptureMove(pos, Move(from,to,cap,wR,0));
			this->addCaptureMove(pos, Move(from,to,cap,wB,0));
			this->addCaptureMove(pos, Move(from,to,cap,wN,0));	
		}
		else
		{
			this->addCaptureMove(pos, Move(from,to,cap,EMPTY,0));
		}
	}
	else
	{
		if(BoardUtils::RankBrd[from] == RANK_2)
		{
			this->addCaptureMove(pos, Move(from,to,cap,bQ,0));
			this->addCaptureMove(pos, Move(from,to,cap,bR,0));
			this->addCaptureMove(pos, Move(from,to,cap,bB,0));
			this->addCaptureMove(pos, Move(from,to,cap,bN,0));	
		}
		else
		{
			this->addCaptureMove(pos, Move(from,to,cap,EMPTY,0));
		}
	}

}

void MoveList::generateBishopMoves(const Board& pos, uint32_t side)
{
	int bi = side == WHITE ? wB : bB;
	for(uint32_t pce = 0; pce < pos.piece_list[bi].size(); ++pce )
	{
		int curBiSq = pos.piece_list[bi][pce];
		for(uint32_t move = 0; move < Attack::BiMoves.size(); ++move )
		{
			int newSq = curBiSq + Attack::BiMoves[move];
			while(pos.sqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceInfo::PieceCol[pos.pieces[newSq]] == (!side))
					{
						this->addCaptureMove(pos, Move(curBiSq, newSq, pos.pieces[newSq], EMPTY, 0));
					}
					break;
				}
				this->addQuietMove(pos, Move(curBiSq, newSq, EMPTY, EMPTY, 0));
				newSq += Attack::BiMoves[move];
			}
		}
	}
}

void MoveList::generateRookMoves(const Board& pos, uint32_t side)
{
	int rk = side == WHITE ? wR : bR;
	for(uint32_t pce = 0; pce < pos.piece_list[rk].size(); ++pce)
	{
		int curRkSq = pos.piece_list[rk][pce];
		for(uint32_t move = 0; move < Attack::RkMoves.size(); ++move)
		{
			int newSq = curRkSq + Attack::RkMoves[move];
			while(pos.sqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceInfo::PieceCol[pos.pieces[newSq]] == (!side))
					{
						this->addCaptureMove(pos, Move(curRkSq, newSq, pos.pieces[newSq], EMPTY, 0));
					}
					break;
				}
				this->addQuietMove(pos, Move(curRkSq, newSq, EMPTY, EMPTY, 0));
				newSq += Attack::RkMoves[move];
			}
		}
	}
}
void MoveList::generateQueenMoves(const Board& pos, uint32_t side)
{
	int Qn = side == WHITE ? wQ : bQ;

	for(uint32_t pce = 0; pce < pos.piece_list[Qn].size(); ++pce)
	{
		int curQn = pos.piece_list[Qn][pce];
		for(uint32_t move = 0; move < Attack::BiMoves.size(); ++move)
		{
			int newSq = curQn + Attack::BiMoves[move];
			while(pos.sqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceInfo::PieceCol[pos.pieces[newSq]] == (!side))
					{
						this->addCaptureMove(pos, Move(curQn, newSq, pos.pieces[newSq], EMPTY, 0));
					}
					break;
				}
					this->addQuietMove(pos, Move(curQn, newSq, EMPTY, EMPTY, 0));
				newSq += Attack::BiMoves[move];
			}
		}
	}

	for(uint32_t pce = 0; pce < pos.piece_list[Qn].size(); ++pce)
	{
		int curQn = pos.piece_list[Qn][pce];
		for(uint32_t move = 0; move < Attack::RkMoves.size(); ++move)
		{
			int newSq = curQn + Attack::RkMoves[move];
			while(pos.sqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceInfo::PieceCol[pos.pieces[newSq]] == (!side))
					{
						this->addCaptureMove(pos, Move(curQn, newSq, pos.pieces[newSq], EMPTY, 0));
					}
					break;
				}
					this->addQuietMove(pos, Move(curQn, newSq, EMPTY, EMPTY, 0));
				newSq += Attack::RkMoves[move];
			}
		}
	}
}
void MoveList::generateSlidingMoves(const Board& pos, uint32_t side)
{
	this->generateBishopMoves(pos, side);
	this->generateRookMoves(pos, side);
	this->generateQueenMoves(pos, side);
}


void MoveList::generateKnightMoves(const Board& pos, uint32_t side)
{
	int kn = side == WHITE ? wN : bN;
	for(uint32_t pce = 0; pce < pos.piece_list[kn].size(); ++pce)
	{
		int curKnSq = pos.piece_list[kn][pce];
		for(uint32_t move = 0; move < Attack::KnMoves.size(); ++move)
		{
			int newSq = curKnSq + Attack::KnMoves[move];
			if(pos.sqOnBoard(newSq))
			{
				if(PieceInfo::PieceCol[pos.pieces[newSq]]== !side)
				{
					this->addCaptureMove(pos, Move(curKnSq, newSq, pos.pieces[newSq], EMPTY, 0));
				}
				if(pos.pieces[newSq] == EMPTY)
				{
					this->addQuietMove(pos, Move(curKnSq, newSq, EMPTY, EMPTY, 0));
				}
			}
		}
	}
}

//*** does not include attacked squares.
void MoveList::generateKingMoves(const Board& pos, uint32_t side)
{
	int ki = side == WHITE ? wK : bK;
	int kingSq = pos.piece_list[ki][0];
	ASSERT(pos.piece_list[ki].size() == 1);
	for(uint32_t move = 0; move < Attack::KiMoves.size(); ++move)
	{
		int newSq = kingSq + Attack::KiMoves[move];
		if(pos.sqOnBoard(newSq) /*&& !pos.sqAttacked(newSq, !side)*/)
		{
			if(pos.pieces[newSq] == EMPTY)
			{
				this->addQuietMove(pos, Move(kingSq, newSq, EMPTY, EMPTY, 0));
			}
			if(PieceInfo::PieceCol[pos.pieces[newSq]]== !side)
			{
				this->addCaptureMove(pos, Move(kingSq, newSq, pos.pieces[newSq], EMPTY, 0));
			}
		}
	}
}
void MoveList::generateNonSlidingMoves(const Board& pos, uint32_t side)
{
	this->generateKnightMoves(pos, side);
	this->generateKingMoves(pos, side);
}


void MoveList::generatePawnMoves(const Board& pos, uint32_t side)
{
	uint32_t oppositeSide = !side;

	int32_t oneMove = side == WHITE ? 10 : -10;
	int32_t twoMove = side == WHITE ? 20 : -20;
	int32_t cap1 = side == WHITE ? 9 : -9;
	int32_t cap2 = side == WHITE ? 11 : -11;
	int pawn = side == WHITE ? wP : bP;

	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pawn].size(); ++pceNum)
	{
		int sq = pos.piece_list[pawn][pceNum];
		ASSERT(sq != OFFBOARD && sq != NO_SQ)
		if(pos.pieces[sq + oneMove] == EMPTY)
		{
			this->addPawnMove(pos, sq, sq + oneMove, side);
			if( ((side == WHITE && BoardUtils::RankBrd[sq] == RANK_2) || (side == BLACK && BoardUtils::RankBrd[sq] == RANK_7)) && pos.pieces[sq + twoMove] == EMPTY)
			{
				this->addQuietMove(pos, Move(sq, sq + twoMove, EMPTY, EMPTY, PS));
			}
		}
		if(pos.sqOnBoard(sq + cap1) && PieceInfo::PieceCol[pos.pieces[sq + cap1]] == oppositeSide)
		{
			this->addPawnCaptureMove(pos, sq, sq + cap1, pos.pieces[sq + cap1], side);
		}
		if(pos.sqOnBoard(sq + cap2) && PieceInfo::PieceCol[pos.pieces[sq + cap2]] == oppositeSide)
		{
			this->addPawnCaptureMove(pos, sq, sq + cap2, pos.pieces[sq + cap2], side);
		}
		if(pos.en_pas != NO_SQ)
		{
			if((unsigned)(sq + cap1) == pos.en_pas)
			{
				this->addEnPasMove(pos, Move(sq, sq + cap1, EMPTY, EMPTY, EP));
			}
			if((unsigned)(sq + cap2) == pos.en_pas)
			{
				this->addEnPasMove(pos, Move(sq, sq + cap2, EMPTY, EMPTY, EP));
			}
		}
	}
}

void MoveList::generateCastlingMoves(const Board& pos, uint32_t side)
{
	if(side == WHITE)
	{
		if(pos.castle_perm & WKCA)
		{
			if(pos.pieces[F1] == EMPTY && pos.pieces[G1] == EMPTY)
			{
				if(!pos.sqAttacked(E1, BLACK) && !pos.sqAttacked(F1, BLACK))
				{
					this->addQuietMove(pos, Move(E1, G1, EMPTY, EMPTY, CA));
				}
			}
		}
		if(pos.castle_perm & WQCA)
		{
			if(pos.pieces[D1] == EMPTY && pos.pieces[C1] == EMPTY && pos.pieces[B1] ==EMPTY)
			{
				if(!pos.sqAttacked(E1, BLACK) && !pos.sqAttacked(D1, BLACK))
				{
					this->addQuietMove(pos, Move(E1, C1, EMPTY, EMPTY, CA));
				}
			}
		}
	}
	else
	{
		if(pos.castle_perm & BKCA)
		{
			if(pos.pieces[F8] == EMPTY && pos.pieces[G8] == EMPTY)
			{
				if(!pos.sqAttacked(E8, WHITE) && !pos.sqAttacked(F8, WHITE))
				{
					this->addQuietMove(pos, Move(E8, G8, EMPTY, EMPTY, CA));
				}
			}
		}
		if(pos.castle_perm & BQCA)
		{
			if(pos.pieces[D8] == EMPTY && pos.pieces[C8] == EMPTY && pos.pieces[B8] ==EMPTY)
			{
				if(!pos.sqAttacked(E8, WHITE) && !pos.sqAttacked(D8, WHITE))
				{
					this->addQuietMove(pos, Move(E8, C8, EMPTY, EMPTY, CA));
				}
			}
		}
	}
}

void MoveList::generateAllMoves(const Board& pos)
{
	ASSERT(checkBoard(pos));
	this->moves.clear();
	this->generatePawnMoves(pos, pos.side_to_move);
	this->generateNonSlidingMoves(pos, pos.side_to_move);
	this->generateSlidingMoves(pos, pos.side_to_move);
	this->generateCastlingMoves(pos, pos.side_to_move);

}

void MoveList::reorderList(int32_t startIdx)
{
	int32_t curBest = 0;
	int32_t bestIdx = startIdx;
	for(uint32_t i = startIdx; i < this->size(); ++i)
	{
		if(this->moves[i].score > curBest)
		{
			curBest = this->moves[i].score;
			bestIdx = i;
		}
	}
	Move tmp = this->moves[startIdx];
	this->moves[startIdx] = this->moves[bestIdx];
	this->moves[bestIdx] = tmp;
}

uint32_t MoveList::size() const
{
	return this->moves.size();
}
const Move& MoveList::operator[](const int idx) const
{
	return moves[idx];
}
Move& MoveList::operator[](const int idx)
{
	return moves[idx];
}
