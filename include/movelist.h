#ifndef MOVELIST_H
#define MOVELIST_H

#include "defs.h"
#include "board.h"
#include "move.h"
#include <vector>
class MoveList
{	
	private:
		void AddQuietMove(Board& pos, Move move);
		void AddCaptureMove(Board& pos, Move move);
		void AddEnPasMove(Board& pos, Move move);

		void AddPawnMove(Board& pos, int from, int to, int side);
		void AddPawnCaptureMove(Board& pos, int from, int to, int cap, int side);
		void GeneratePawnMoves(Board& pos, int side);
		void GenerateBishopMoves(Board& pos, int side);
		void GenerateRookMoves(Board& pos, int side);
		void GenerateQueenMoves(Board& pos, int side);
		void GenerateKnightMoves(Board& pos, int side);
		void GenerateKingMoves(Board& pos, int side);
		void GenerateSlidingMoves(Board& pos, int side);
		void GenerateNonSlidingMoves(Board& pos, int side);
		void GenerateCastlingMoves(Board& psd, int side);

	public:
		// possibly use linked list instead of vector
		std::vector<Move> moves;

		MoveList();

		void GenerateAllMoves(Board& pos);
		void PrintMoveList();
};


#endif