#ifndef MOVELIST_H
#define MOVELIST_H

#include "defs.h"
#include "board.h"
#include "move.h"
#include <vector>

//used in move ordering. MostValuableVictim-LeastValuableAttacker
namespace MvvLva
{
	extern std::array<std::array<int32_t, PCE_TYPES>, PCE_TYPES> MvvLvaScore;
	constexpr std::array<int32_t, PCE_TYPES> victimScore {0, 100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600};

}

class MoveList
{	
	private:
		// Creates and adds a type of move to eh movelist
		void addQuietMove(const Board& pos, Move&& move) noexcept;
		void addCaptureMove(const Board& pos, Move&& move) noexcept;
		void addEnPasMove(const Board& pos, Move&& move) noexcept;

		// add's each piece's move
		void addPawnMove(const Board& pos, uint32_t from, uint32_t to, uint32_t side) noexcept;
		void addPawnCaptureMove(const Board& pos, uint32_t from, uint32_t to, uint32_t cap, uint32_t side) noexcept;
		void generatePawnMoves(const Board& pos, uint32_t side) noexcept;
		void generateBishopMoves(const Board& pos, uint32_t side) noexcept;
		void generateRookMoves(const Board& pos, uint32_t side) noexcept;
		void generateQueenMoves(const Board& pos, uint32_t side) noexcept;
		void generateKnightMoves(const Board& pos, uint32_t side) noexcept;
		void generateKingMoves(const Board& pos, uint32_t side) noexcept;
		void generateSlidingMoves(const Board& pos, uint32_t side) noexcept;
		void generateNonSlidingMoves(const Board& pos, uint32_t side) noexcept;
		void generateCastlingMoves(const Board& psd, uint32_t side) noexcept;

		std::vector<Move> moves;

	public:
		const uint32_t MAX_MOVES_PER_POSITION = 256;
		const uint32_t PVMOVE_OFFSET = 	2000000;
		const uint32_t CAPTURE_OFFSET = 1000000;
		// Any non-capture move that changes the beta-cutoff
		const uint32_t KILLER_OFFSET1 = 900000;
		const uint32_t KILLER_OFFSET2 = 800000;
		
		MoveList() noexcept; 
		MoveList(const MoveList& o) noexcept;
		MoveList(MoveList&& o) noexcept;
		void generateAllMoves(const Board& pos) noexcept;
		void generateAllCaptureMoves(const Board& pos) noexcept;
		void reorderList(int32_t idx) noexcept;
		uint32_t size() const noexcept;
		const Move& operator[](const int idx) const noexcept;
		Move& operator[](const int idx) noexcept;
		// void printMoveList();
};


#endif
