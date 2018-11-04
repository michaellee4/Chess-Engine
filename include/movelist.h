#ifndef MOVELIST_H
#define MOVELIST_H

#include "defs.h"
#include "board.h"
#include "move.h"
#include <vector>
class MoveList
{	
	private:
		void AddPawnMove(Board& pos, int from, int to, int side);
		void AddPawnCaptureMove(Board& pos, int from, int to, int cap, int side);
		void GeneratePawnMoves(Board& pos, int side);
	public:
		std::vector<Move> moves;

		MoveList();

		void AddQuietMove(Board& pos, Move move);
		void AddCaptureMove(Board& pos, Move move);
		void AddEnPasMove(Board& pos, Move move);
		void GenerateAllMoves(Board& pos);
		void PrintMoveList();
};


#endif