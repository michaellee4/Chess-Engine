#include "movelist.h"

// MoveList::MoveList()
// {
	
// }

void MoveList::PrintMoveList()
{
	for(int i = 0; i < this->count; i ++)
	{
		Move curMove = this->moves[i];
		printf("Move: %d > %s (score: %d)\n",i ,curMove.ToString().c_str(), curMove.score );
	}
		printf("MoveList Total: %d Moves\n", this->count );
}

void MoveList::AddQuietMove(Board& pos, Move move)
{
	this->moves[this->count] = move;
	this->count++;
}
void MoveList::AddCaptureMove(Board& pos, Move move)
{
	this->moves[this->count] = move;
	this->count++;
}
void MoveList::AddEnPasMove(Board& pos, Move move)
{
	this->moves[this->count] = move;
	this->count++;
}

void MoveList::AddWhitePawnMove(Board& pos, int from, int to)
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
void MoveList::AddWhitePawnCaptureMove(Board& pos, int from, int to, int cap)
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
			this->AddWhitePawnMove(pos, sq, sq + oneMove);
			if( ((side == WHITE && RankBrd[sq] == RANK_2) || (side == BLACK && RankBrd[sq] == RANK_7)) && pos.pieces[sq + twoMove] == EMPTY)
			{
				this->AddQuietMove(pos, Move(sq, sq + twoMove, EMPTY, EMPTY, PS));
			}
		}
		if(pos.SqOnBoard(sq + cap1) && PieceCol[pos.pieces[sq + cap1]] == oppositeSide)
		{
			this->AddWhitePawnCaptureMove(pos, sq, sq + cap1, pos.pieces[sq + cap1]);
		}
		if(pos.SqOnBoard(sq + cap2) && PieceCol[pos.pieces[sq + cap2]] == oppositeSide)
		{
			this->AddWhitePawnCaptureMove(pos, sq, sq + cap2, pos.pieces[sq + cap2]);
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
	this->count = 0;
	this->GeneratePawnMoves(pos, pos.side_to_move);
}