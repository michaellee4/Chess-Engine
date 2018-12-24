#ifndef MOVELIST_H
#define MOVELIST_H

#include "defs.h"
#include "board.h"
#include "move.h"
#include <vector>

class MoveList
{	
	private:
		const uint32_t MAX_MOVES_PER_POSITION = 256;
		// Creates and adds a type of move to eh movelist
		void addQuietMove(Board& pos, Move move);
		void addCaptureMove(Board& pos, Move move);
		void addEnPasMove(Board& pos, Move move);

		// add's each piece's move
		void addPawnMove(Board& pos, uint32_t from, uint32_t to, uint32_t side);
		void addPawnCaptureMove(Board& pos, uint32_t from, uint32_t to, uint32_t cap, uint32_t side);
		void generatePawnMoves(Board& pos, uint32_t side);
		void generateBishopMoves(Board& pos, uint32_t side);
		void generateRookMoves(Board& pos, uint32_t side);
		void generateQueenMoves(Board& pos, uint32_t side);
		void generateKnightMoves(Board& pos, uint32_t side);
		void generateKingMoves(Board& pos, uint32_t side);
		void generateSlidingMoves(Board& pos, uint32_t side);
		void generateNonSlidingMoves(Board& pos, uint32_t side);
		void generateCastlingMoves(Board& psd, uint32_t side);
		std::vector<Move> moves;

	public:

		MoveList();

		void generateAllMoves(Board& pos);
		uint32_t size() const;
		const Move& operator[](const int idx) const;
		Move& operator[](const int idx);
		// void printMoveList();
};


#endif
