#ifndef MOVELIST_H
#define MOVELIST_H

#include "defs.h"
#include "board.h"
#include "move.h"
class MoveList
{
	public:
		Move moves[MAXPOSITIONMOVES];
		int count;

		void AddQuietMove(Board& pos, int move);
		void AddCaptureMove(Board& pos, int move);
		void AddEnPasMove(Board& pos, int move);
		void GenerateAllMoves(Board& pos);
		void PrintMoveList();
};


#endif