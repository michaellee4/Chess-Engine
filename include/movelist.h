#ifndef MOVELIST_H
#define MOVELIST_H

#include "defs.h"
#include "board.h"
#include "move.h"
#include <vector>

class MoveList
{	
	private:
		// Creates and adds a type of move to eh movelist
		void AddQuietMove(Board& pos, Move move);
		void AddCaptureMove(Board& pos, Move move);
		void AddEnPasMove(Board& pos, Move move);

		// Add's each piece's move
		void AddPawnMove(Board& pos, uint32_t from, uint32_t to, uint32_t side);
		void AddPawnCaptureMove(Board& pos, uint32_t from, uint32_t to, uint32_t cap, uint32_t side);
		void GeneratePawnMoves(Board& pos, uint32_t side);
		void GenerateBishopMoves(Board& pos, uint32_t side);
		void GenerateRookMoves(Board& pos, uint32_t side);
		void GenerateQueenMoves(Board& pos, uint32_t side);
		void GenerateKnightMoves(Board& pos, uint32_t side);
		void GenerateKingMoves(Board& pos, uint32_t side);
		void GenerateSlidingMoves(Board& pos, uint32_t side);
		void GenerateNonSlidingMoves(Board& pos, uint32_t side);
		void GenerateCastlingMoves(Board& psd, uint32_t side);

	public:
		std::vector<Move> moves;

		MoveList();

		void GenerateAllMoves(Board& pos);
		uint32_t size();
		Move& operator[](const int idx);
		// void PrintMoveList();
};


#endif
