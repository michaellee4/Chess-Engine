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
		void addQuietMove(const Board& pos, const Move&& move);
		void addCaptureMove(const Board& pos, const Move&& move);
		void addEnPasMove(const Board& pos, const Move&& move);

		// add's each piece's move
		void addPawnMove(const Board& pos, uint32_t from, uint32_t to, uint32_t side);
		void addPawnCaptureMove(const Board& pos, uint32_t from, uint32_t to, uint32_t cap, uint32_t side);
		void generatePawnMoves(const Board& pos, uint32_t side);
		void generateBishopMoves(const Board& pos, uint32_t side);
		void generateRookMoves(const Board& pos, uint32_t side);
		void generateQueenMoves(const Board& pos, uint32_t side);
		void generateKnightMoves(const Board& pos, uint32_t side);
		void generateKingMoves(const Board& pos, uint32_t side);
		void generateSlidingMoves(const Board& pos, uint32_t side);
		void generateNonSlidingMoves(const Board& pos, uint32_t side);
		void generateCastlingMoves(const Board& psd, uint32_t side);
		std::vector<Move> moves;

	public:

		MoveList();

		void generateAllMoves(const Board& pos);
		uint32_t size() const;
		const Move& operator[](const int idx) const;
		Move& operator[](const int idx);
		// void printMoveList();
};


#endif
