#include "movelist.h"
void MoveList::PrintMoveList()
{
	for(int i = 0; i < this->count; i ++)
	{
		Move curMove = this->moves[i];
		printf("Move: %d > %s (score: %d)\n",curMove.move ,curMove.ToString().c_str(), curMove.score );
	}
		printf("MoveList Total: %d Moves\n", this->count );
}

void MoveList::AddQuietMove(Board& pos, int move)
{
	this->moves[this->count].move = move;
	this->moves[this->count].score = 0;
	this->count++;
}
void MoveList::AddCaptureMove(Board& pos, int move)
{
	this->moves[this->count].move = move;
	this->moves[this->count].score = 0;
	this->count++;
}
void MoveList::AddEnPasMove(Board& pos, int move)
{
	this->moves[this->count].move = move;
	this->moves[this->count].score = 0;
	this->count++;
}
void MoveList::GenerateAllMoves(Board& pos)
{
	this->count = 0;
}