#ifndef MOVELIST_H
#define MOVELIST_H

#include "defs.h"
#include "board.h"
#include "move.h"
class MoveList
{	
	private:
		void AddWhitePawnMove(Board& pos, int from, int to);
		void AddWhitePawnCaptureMove(Board& pos, int from, int to, int cap);
		void GeneratePawnMoves(Board& pos, int side);
	public:
		// Change this to a vector with initial Capacity later
		Move moves[MAXPOSITIONMOVES];
		int count;

		//MoveList();

		void AddQuietMove(Board& pos, Move move);
		void AddCaptureMove(Board& pos, Move move);
		void AddEnPasMove(Board& pos, Move move);
		void GenerateAllMoves(Board& pos);
		void PrintMoveList();
};


#endif