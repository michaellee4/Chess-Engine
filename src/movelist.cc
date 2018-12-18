#include "movelist.h"
#include <bitset>
#include <iostream>

MoveList::MoveList()
{
	moves.reserve(MAXPOSITIONMOVES);
}

// void MoveList::PrintMoveList()
// {
// 	for(uint32_t i = 0; i < this->moves.size(); ++i)
// 	{
// 		Move curMove = this->moves[i];
// 		printf("Move: %02d > %s (score: %d) : ",i ,curMove.ToString().c_str(), curMove.score );
// 		std::bitset<32> bits(curMove.move);
// 		std::cout <<  bits <<std::endl;
// 	}
// 		printf("MoveList Total: %lu Moves\n\n", this->moves.size() );
// }

void MoveList::AddQuietMove(Board& pos, Move move)
{
	this->moves.push_back(move);
}
void MoveList::AddCaptureMove(Board& pos, Move move)
{
	this->moves.push_back(move);
}
void MoveList::AddEnPasMove(Board& pos, Move move)
{
	this->moves.push_back(move);
}

void MoveList::AddPawnMove(Board& pos, uint32_t from, uint32_t to, uint32_t side)
{
	if(side == WHITE)
	{
		if(RankBrd[from] == RANK_7)
		{
			this->AddQuietMove(pos, Move(from,to,EMPTY,wQ,0));
			this->AddQuietMove(pos, Move(from,to,EMPTY,wR,0));
			this->AddQuietMove(pos, Move(from,to,EMPTY,wB,0));
			this->AddQuietMove(pos, Move(from,to,EMPTY,wN,0));
		}
		else
		{
			this->AddQuietMove(pos, Move(from,to,EMPTY,EMPTY,0));
		}	
	}
	else
	{
		if(RankBrd[from] == RANK_2)
		{
			this->AddQuietMove(pos, Move(from,to,EMPTY,bQ,0));
			this->AddQuietMove(pos, Move(from,to,EMPTY,bR,0));
			this->AddQuietMove(pos, Move(from,to,EMPTY,bB,0));
			this->AddQuietMove(pos, Move(from,to,EMPTY,bN,0));
		}
		else
		{
			this->AddQuietMove(pos, Move(from,to,EMPTY,EMPTY,0));
		}	
	}

}
void MoveList::AddPawnCaptureMove(Board& pos, uint32_t from, uint32_t to, uint32_t cap, uint32_t side)
{
	if(side == WHITE)
	{
		if(RankBrd[from] == RANK_7)
		{
			this->AddCaptureMove(pos, Move(from,to,cap,wQ,0));
			this->AddCaptureMove(pos, Move(from,to,cap,wR,0));
			this->AddCaptureMove(pos, Move(from,to,cap,wB,0));
			this->AddCaptureMove(pos, Move(from,to,cap,wN,0));	
		}
		else
		{
			this->AddCaptureMove(pos, Move(from,to,cap,EMPTY,0));
		}
	}
	else
	{
		if(RankBrd[from] == RANK_2)
		{
			this->AddCaptureMove(pos, Move(from,to,cap,bQ,0));
			this->AddCaptureMove(pos, Move(from,to,cap,bR,0));
			this->AddCaptureMove(pos, Move(from,to,cap,bB,0));
			this->AddCaptureMove(pos, Move(from,to,cap,bN,0));	
		}
		else
		{
			this->AddCaptureMove(pos, Move(from,to,cap,EMPTY,0));
		}
	}

}

void MoveList::GenerateBishopMoves(Board& pos, uint32_t side)
{
	int bi = side == WHITE ? wB : bB;
	for(uint32_t pce = 0; pce < pos.piece_list[bi].size(); ++pce )
	{
		int curBiSq = pos.piece_list[bi][pce];
		for(uint32_t move = 0; move < Attack::BiMoves.size(); ++move )
		{
			int newSq = curBiSq + Attack::BiMoves[move];
			while(pos.SqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceInfo::PieceCol[pos.pieces[newSq]] == (!side))
					{
						this->AddCaptureMove(pos, Move(curBiSq, newSq, pos.pieces[newSq], EMPTY, 0));
					}
					break;
				}
					this->AddQuietMove(pos, Move(curBiSq, newSq, EMPTY, EMPTY, 0));
				newSq += Attack::BiMoves[move];
			}
		}
	}
}

void MoveList::GenerateRookMoves(Board& pos, uint32_t side)
{
	int rk = side == WHITE ? wR : bR;
	for(uint32_t pce = 0; pce < pos.piece_list[rk].size(); ++pce)
	{
		int curRkSq = pos.piece_list[rk][pce];
		for(uint32_t move = 0; move < Attack::RkMoves.size(); ++move)
		{
			int newSq = curRkSq + Attack::RkMoves[move];
			while(pos.SqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceInfo::PieceCol[pos.pieces[newSq]] == (!side))
					{
						this->AddCaptureMove(pos, Move(curRkSq, newSq, pos.pieces[newSq], EMPTY, 0));
					}
					break;
				}
					this->AddQuietMove(pos, Move(curRkSq, newSq, EMPTY, EMPTY, 0));
				newSq += Attack::RkMoves[move];
			}
		}
	}
}
void MoveList::GenerateQueenMoves(Board& pos, uint32_t side)
{
	int Qn = side == WHITE ? wQ : bQ;

	for(uint32_t pce = 0; pce < pos.piece_list[Qn].size(); ++pce)
	{
		int curQn = pos.piece_list[Qn][pce];
		for(uint32_t move = 0; move < Attack::BiMoves.size(); ++move)
		{
			int newSq = curQn + Attack::BiMoves[move];
			while(pos.SqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceInfo::PieceCol[pos.pieces[newSq]] == (!side))
					{
						this->AddCaptureMove(pos, Move(curQn, newSq, pos.pieces[newSq], EMPTY, 0));
					}
					break;
				}
					this->AddQuietMove(pos, Move(curQn, newSq, EMPTY, EMPTY, 0));
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
			while(pos.SqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceInfo::PieceCol[pos.pieces[newSq]] == (!side))
					{
						this->AddCaptureMove(pos, Move(curQn, newSq, pos.pieces[newSq], EMPTY, 0));
					}
					break;
				}
					this->AddQuietMove(pos, Move(curQn, newSq, EMPTY, EMPTY, 0));
				newSq += Attack::RkMoves[move];
			}
		}
	}
}
void MoveList::GenerateSlidingMoves(Board& pos, uint32_t side)
{
	this->GenerateBishopMoves(pos, side);
	this->GenerateRookMoves(pos, side);
	this->GenerateQueenMoves(pos, side);
}


void MoveList::GenerateKnightMoves(Board& pos, uint32_t side)
{
	int kn = side == WHITE ? wN : bN;
	for(uint32_t pce = 0; pce < pos.piece_list[kn].size(); ++pce)
	{
		int curKnSq = pos.piece_list[kn][pce];
		for(uint32_t move = 0; move < Attack::KnMoves.size(); ++move)
		{
			int newSq = curKnSq + Attack::KnMoves[move];
			if(pos.SqOnBoard(newSq))
			{
				if(PieceInfo::PieceCol[pos.pieces[newSq]]== !side)
				{
					this->AddCaptureMove(pos, Move(curKnSq, newSq, pos.pieces[newSq], EMPTY, 0));
				}
				if(pos.pieces[newSq] == EMPTY)
				{
					this->AddQuietMove(pos, Move(curKnSq, newSq, EMPTY, EMPTY, 0));
				}
			}
		}
	}
}

//*** does not include attacked squares.
void MoveList::GenerateKingMoves(Board& pos, uint32_t side)
{
	int ki = side == WHITE ? wK : bK;
	int kingSq = pos.piece_list[ki][0];
	ASSERT(pos.piece_list[ki].size() == 1);
	for(uint32_t move = 0; move < Attack::KiMoves.size(); ++move)
	{
		int newSq = kingSq + Attack::KiMoves[move];
		if(pos.SqOnBoard(newSq) /*&& !pos.SqAttacked(newSq, !side)*/)
		{
			if(pos.pieces[newSq] == EMPTY)
			{
				this->AddQuietMove(pos, Move(kingSq, newSq, EMPTY, EMPTY, 0));
			}
			if(PieceInfo::PieceCol[pos.pieces[newSq]]== !side)
			{
				this->AddCaptureMove(pos, Move(kingSq, newSq, pos.pieces[newSq], EMPTY, 0));
			}
		}
	}
}
void MoveList::GenerateNonSlidingMoves(Board& pos, uint32_t side)
{
	this->GenerateKnightMoves(pos, side);
	this->GenerateKingMoves(pos, side);
}


void MoveList::GeneratePawnMoves(Board& pos, uint32_t side)
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
			this->AddPawnMove(pos, sq, sq + oneMove, side);
			if( ((side == WHITE && RankBrd[sq] == RANK_2) || (side == BLACK && RankBrd[sq] == RANK_7)) && pos.pieces[sq + twoMove] == EMPTY)
			{
				this->AddQuietMove(pos, Move(sq, sq + twoMove, EMPTY, EMPTY, PS));
			}
		}
		if(pos.SqOnBoard(sq + cap1) && PieceInfo::PieceCol[pos.pieces[sq + cap1]] == oppositeSide)
		{
			this->AddPawnCaptureMove(pos, sq, sq + cap1, pos.pieces[sq + cap1], side);
		}
		if(pos.SqOnBoard(sq + cap2) && PieceInfo::PieceCol[pos.pieces[sq + cap2]] == oppositeSide)
		{
			this->AddPawnCaptureMove(pos, sq, sq + cap2, pos.pieces[sq + cap2], side);
		}
		if(pos.en_pas != NO_SQ)
		{
			if(sq + cap1 == (int32_t)pos.en_pas)
			{
				this->AddEnPasMove(pos, Move(sq, sq + cap1, EMPTY, EMPTY, EP));
			}
			if(sq + cap2 == (int32_t) pos.en_pas)
			{
				this->AddEnPasMove(pos, Move(sq, sq + cap2, EMPTY, EMPTY, EP));
			}
		}
	}
}

void MoveList::GenerateCastlingMoves(Board& pos, uint32_t side)
{
	if(side == WHITE)
	{
		if(pos.castle_perm & WKCA)
		{
			if(pos.pieces[F1] == EMPTY && pos.pieces[G1] == EMPTY)
			{
				if(!pos.SqAttacked(E1, BLACK) && !pos.SqAttacked(F1, BLACK))
				{
					this->AddQuietMove(pos, Move(E1, G1, EMPTY, EMPTY, CA));
				}
			}
		}
		if(pos.castle_perm & WQCA)
		{
			if(pos.pieces[D1] == EMPTY && pos.pieces[C1] == EMPTY && pos.pieces[B1] ==EMPTY)
			{
				if(!pos.SqAttacked(E1, BLACK) && !pos.SqAttacked(D1, BLACK))
				{
					this->AddQuietMove(pos, Move(E1, C1, EMPTY, EMPTY, CA));
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
				if(!pos.SqAttacked(E8, WHITE) && !pos.SqAttacked(F8, WHITE))
				{
					this->AddQuietMove(pos, Move(E8, G8, EMPTY, EMPTY, CA));
				}
			}
		}
		if(pos.castle_perm & BQCA)
		{
			if(pos.pieces[D8] == EMPTY && pos.pieces[C8] == EMPTY && pos.pieces[B8] ==EMPTY)
			{
				if(!pos.SqAttacked(E8, WHITE) && !pos.SqAttacked(D8, WHITE))
				{
					this->AddQuietMove(pos, Move(E8, C8, EMPTY, EMPTY, CA));
				}
			}
		}
	}
}

void MoveList::GenerateAllMoves(Board& pos)
{
	ASSERT(CheckBoard(pos));
	this->moves.clear();
	this->GeneratePawnMoves(pos, pos.side_to_move);
	this->GenerateSlidingMoves(pos, pos.side_to_move);
	this->GenerateNonSlidingMoves(pos, pos.side_to_move);
	this->GenerateCastlingMoves(pos, pos.side_to_move);
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