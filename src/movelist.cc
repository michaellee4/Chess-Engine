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
		printf("MoveList Total: %d Moves\n", this->moves.size() );
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
		printf("Bishop on %s %i\n",Board::SqToString(curBiSq).c_str(), side );
		for(int move = 0; move < BiMoves.size(); move ++)
		{
			int newSq = curBiSq + BiMoves[move];
			while(pos.SqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceCol[pos.pieces[newSq]] == (!side))
					{
						printf("Capture Bishop Move to %s\n",Board::SqToString(newSq).c_str() );
					}
					break;
				}
				printf("Empty Bishop Move to %s\n",Board::SqToString(newSq).c_str() );
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
		printf("Rook on %s %i\n",Board::SqToString(curRkSq).c_str(), side );
		for(int move = 0; move < RkMoves.size(); move ++)
		{
			int newSq = curRkSq + RkMoves[move];
			while(pos.SqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceCol[pos.pieces[newSq]] == (!side))
					{
						printf("Capture Rook Move to %s\n",Board::SqToString(newSq).c_str() );
					}
					break;
				}
				printf("Empty Rook Move to %s\n",Board::SqToString(newSq).c_str() );
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
		printf("Queen on %s %i\n",Board::SqToString(curQn).c_str(), side );
		for(int move = 0; move < BiMoves.size(); move ++)
		{
			int newSq = curQn + BiMoves[move];
			while(pos.SqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceCol[pos.pieces[newSq]] == (!side))
					{
						printf("Capture Queen Move to %s\n",Board::SqToString(newSq).c_str() );
					}
					break;
				}
				printf("Empty Queen Move to %s\n",Board::SqToString(newSq).c_str() );
				newSq += BiMoves[move];
			}
		}
	}

	for(int pce = 0; pce < pos.piece_num[Qn]; pce ++)
	{
		int curQn = pos.piece_list[Qn][pce];
		printf("Queen on %s %i\n",Board::SqToString(curQn).c_str(), side );
		for(int move = 0; move < RkMoves.size(); move ++)
		{
			int newSq = curQn + RkMoves[move];
			while(pos.SqOnBoard(newSq))
			{
				if(pos.pieces[newSq] != EMPTY)
				{
					if(PieceCol[pos.pieces[newSq]] == (!side))
					{
						printf("Capture Queen Move to %s\n",Board::SqToString(newSq).c_str() );
					}
					break;
				}
				printf("Empty Queen Move to %s\n",Board::SqToString(newSq).c_str() );
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
		printf("Knight on %s %i\n",Board::SqToString(curKnSq).c_str(), side );
		for(int move = 0; move < KnMoves.size(); move ++)
		{
			int newSq = curKnSq + KnMoves[move];
			if(pos.SqOnBoard(newSq))
			{
				if(PieceCol[pos.pieces[newSq]]== (!side))
				{
					printf("Capture Knight Move to %s\n",Board::SqToString(newSq).c_str() );
				}
				if(pos.pieces[newSq] == EMPTY)
				{
					printf("Empty Knight Move to %s\n",Board::SqToString(newSq).c_str() );
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
	printf("King on %s\n",Board::SqToString(kingSq).c_str() );
	for(int move = 0; move < KiMoves.size(); move ++)
	{
		int newSq = kingSq + KiMoves[move];
		if(pos.SqOnBoard(newSq) && !pos.SqAttacked(newSq, !side))
		{
			if(pos.pieces[newSq] == EMPTY)
			{
				printf("Empty King Move to %s\n",Board::SqToString(newSq).c_str() );
			}
			if(PieceCol[pos.pieces[newSq]]== !side)
			{
				printf("Capture King Move to %s\n",Board::SqToString(newSq).c_str() );
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
void MoveList::GenerateAllMoves(Board& pos)
{
	ASSERT(CheckBoard(pos));
	this->moves.clear();
	this->GeneratePawnMoves(pos, pos.side_to_move);
	this->GenerateSlidingMoves(pos, pos.side_to_move);
	this->GenerateNonSlidingMoves(pos, pos.side_to_move);
}