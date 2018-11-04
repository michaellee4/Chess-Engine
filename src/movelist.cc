#include "movelist.h"

MoveList::MoveList()
{
	moves.reserve(MAXPOSITIONMOVES);
}

void MoveList::PrintMoveList()
{
	for(int i = 0; i < this->moves.size(); i ++)
	{
		Move curMove = this->moves[i];
		printf("Move: %d > %s (score: %d)\n",i ,curMove.ToString().c_str(), curMove.score );
	}
		printf("MoveList Total: %d Moves\n\n", this->moves.size() );
}

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

void MoveList::AddPawnMove(Board& pos, int from, int to, int side)
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
void MoveList::AddPawnCaptureMove(Board& pos, int from, int to, int cap, int side)
{
	if(side == WHITE)
	{
		if(RankBrd[from] == RANK_7)
		{
			this->AddCaptureMove(pos, Move(from,to,cap,wQ,CAP));
			this->AddCaptureMove(pos, Move(from,to,cap,wR,CAP));
			this->AddCaptureMove(pos, Move(from,to,cap,wB,CAP));
			this->AddCaptureMove(pos, Move(from,to,cap,wN,CAP));	
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
			this->AddCaptureMove(pos, Move(from,to,cap,bQ,CAP));
			this->AddCaptureMove(pos, Move(from,to,cap,bR,CAP));
			this->AddCaptureMove(pos, Move(from,to,cap,bB,CAP));
			this->AddCaptureMove(pos, Move(from,to,cap,bN,CAP));	
		}
		else
		{
			this->AddCaptureMove(pos, Move(from,to,cap,EMPTY,0));
		}
	}

}

void MoveList::GenerateBishopMoves(Board& pos, int side)
{
	int bi = side == WHITE ? wB : bB;
	for(int pce = 0; pce < pos.piece_num[bi]; pce ++)
	{
		int curBiSq = pos.piece_list[bi][pce];
		for(int move = 0; move < BiMoves.size(); move ++)
		{
			int newSq = curBiSq + BiMoves[move];
			while(pos.SqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceCol[pos.pieces[newSq]] == (!side))
					{
						this->AddCaptureMove(pos, Move(curBiSq, newSq, pos.pieces[newSq], EMPTY, CAP));
					}
					break;
				}
					this->AddQuietMove(pos, Move(curBiSq, newSq, EMPTY, EMPTY, 0));
				newSq += BiMoves[move];
			}
		}
	}
}

void MoveList::GenerateRookMoves(Board& pos, int side)
{
	int rk = side == WHITE ? wR : bR;
	for(int pce = 0; pce < pos.piece_num[rk]; pce ++)
	{
		int curRkSq = pos.piece_list[rk][pce];
		for(int move = 0; move < RkMoves.size(); move ++)
		{
			int newSq = curRkSq + RkMoves[move];
			while(pos.SqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceCol[pos.pieces[newSq]] == (!side))
					{
						this->AddCaptureMove(pos, Move(curRkSq, newSq, pos.pieces[newSq], EMPTY, CAP));
					}
					break;
				}
					this->AddQuietMove(pos, Move(curRkSq, newSq, EMPTY, EMPTY, 0));
				newSq += RkMoves[move];
			}
		}
	}
}
void MoveList::GenerateQueenMoves(Board& pos, int side)
{
	int Qn = side == WHITE ? wQ : bQ;

	for(int pce = 0; pce < pos.piece_num[Qn]; pce ++)
	{
		int curQn = pos.piece_list[Qn][pce];
		for(int move = 0; move < BiMoves.size(); move ++)
		{
			int newSq = curQn + BiMoves[move];
			while(pos.SqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceCol[pos.pieces[newSq]] == (!side))
					{
						this->AddCaptureMove(pos, Move(curQn, newSq, pos.pieces[newSq], EMPTY, CAP));
					}
					break;
				}
					this->AddQuietMove(pos, Move(curQn, newSq, EMPTY, EMPTY, 0));
				newSq += BiMoves[move];
			}
		}
	}

	for(int pce = 0; pce < pos.piece_num[Qn]; pce ++)
	{
		int curQn = pos.piece_list[Qn][pce];
		for(int move = 0; move < RkMoves.size(); move ++)
		{
			int newSq = curQn + RkMoves[move];
			while(pos.SqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceCol[pos.pieces[newSq]] == (!side))
					{
						this->AddCaptureMove(pos, Move(curQn, newSq, pos.pieces[newSq], EMPTY, CAP));
					}
					break;
				}
					this->AddQuietMove(pos, Move(curQn, newSq, EMPTY, EMPTY, 0));
				newSq += RkMoves[move];
			}
		}
	}
}
void MoveList::GenerateSlidingMoves(Board& pos, int side)
{
	this->GenerateBishopMoves(pos, side);
	this->GenerateRookMoves(pos, side);
	this->GenerateQueenMoves(pos, side);
}


void MoveList::GenerateKnightMoves(Board& pos, int side)
{
	int kn = side == WHITE ? wN : bN;
	for(int pce = 0; pce < pos.piece_num[kn]; pce ++)
	{
		int curKnSq = pos.piece_list[kn][pce];
		for(int move = 0; move < KnMoves.size(); move ++)
		{
			int newSq = curKnSq + KnMoves[move];
			if(pos.SqOnBoard(newSq))
			{
				if(PieceCol[pos.pieces[newSq]]== !side)
				{
					this->AddCaptureMove(pos, Move(curKnSq, newSq, pos.pieces[newSq], EMPTY, CAP));
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
void MoveList::GenerateKingMoves(Board& pos, int side)
{
	int ki = side == WHITE ? wK : bK;
	int kingSq = pos.piece_list[ki][0];
	ASSERT(pos.piece_num[ki] == 1);
	for(int move = 0; move < KiMoves.size(); move ++)
	{
		int newSq = kingSq + KiMoves[move];
		if(pos.SqOnBoard(newSq) /*&& !pos.SqAttacked(newSq, !side)*/)
		{
			if(pos.pieces[newSq] == EMPTY)
			{
				this->AddQuietMove(pos, Move(kingSq, newSq, EMPTY, EMPTY, 0));
			}
			if(PieceCol[pos.pieces[newSq]]== !side)
			{
				this->AddCaptureMove(pos, Move(kingSq, newSq, pos.pieces[newSq], EMPTY, CAP));
			}
		}
	}
}
void MoveList::GenerateNonSlidingMoves(Board& pos, int side)
{
	this->GenerateKnightMoves(pos, side);
	this->GenerateKingMoves(pos, side);
}


void MoveList::GeneratePawnMoves(Board& pos, int side)
{
	int oppositeSide = !side;

	int oneMove = side == WHITE ? 10 : -10;
	int twoMove = side == WHITE ? 20 : -20;
	int cap1 = side == WHITE ? 9 : -9;
	int cap2 = side == WHITE ? 11 : -11;
	int pawn = side == WHITE ? wP : bP;

	for(int pceNum = 0; pceNum < pos.piece_num[pawn]; pceNum++)
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
		if(pos.SqOnBoard(sq + cap1) && PieceCol[pos.pieces[sq + cap1]] == oppositeSide)
		{
			this->AddPawnCaptureMove(pos, sq, sq + cap1, pos.pieces[sq + cap1], side);
		}
		if(pos.SqOnBoard(sq + cap2) && PieceCol[pos.pieces[sq + cap2]] == oppositeSide)
		{
			this->AddPawnCaptureMove(pos, sq, sq + cap2, pos.pieces[sq + cap2], side);
		}
		if(sq + cap1 == pos.en_pas)
		{
			this->AddCaptureMove(pos, Move(sq, sq + cap1, EMPTY, EMPTY, EP));
		}
		if(sq + cap2 == pos.en_pas)
		{
			this->AddCaptureMove(pos, Move(sq, sq + cap2, EMPTY, EMPTY, EP));
		}
	}
}

void MoveList::GenerateCastlingMoves(Board& pos, int side)
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
			if(pos.pieces[D1] == EMPTY && pos.pieces[C1] == EMPTY & pos.pieces[B1] ==EMPTY)
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
			if(pos.pieces[D8] == EMPTY && pos.pieces[C8] == EMPTY & pos.pieces[B8] ==EMPTY)
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