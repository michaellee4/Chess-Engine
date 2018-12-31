#ifndef MOVELIST_H
#define MOVELIST_H

#include "defs.h"
#include "board.h"
#include "move.h"

//used in move ordering. MostValuableVictim-LeastValuableAttacker
namespace MvvLva
{
	extern std::array<std::array<int32_t, kNumPceTypes>, kNumPceTypes> MvvLvaScore;
	constexpr std::array<int32_t, kNumPceTypes> victimScore {0, 100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600};
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

		static constexpr uint32_t kMaxPossibleMoves = 256;
		static constexpr uint32_t kCaptureBonus = 1000000;
		// Any non-capture move that changes the beta-cutoff
		static constexpr uint32_t kPrimaryKillerBonus = 900000;
		static constexpr uint32_t kSecondaryKillerBonus = 800000;

		std::vector<Move> moves;

	public:
		static constexpr uint32_t kPvMoveBonus = 2000000;
		
		MoveList() noexcept; 
		MoveList(const MoveList& o);
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
