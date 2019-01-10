/**
*	@file movelist.h
*	@brief Custom data structure to store possible moves
*	@author Michael Lee
*	@date 1/9/2019
*/

#ifndef MOVELIST_H
#define MOVELIST_H

#include "defs.h"
#include "board.h"
#include "move.h"

/** 
* used in move ordering. MostValuableVictim-LeastValuableAttacker
*/
namespace MvvLva
{
	extern std::array<std::array<int32_t, kNumPceTypes>, kNumPceTypes> MvvLvaScore;
	constexpr std::array<int32_t, kNumPceTypes> victimScore {0, 100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600};
}

class MoveList
{	
private:
/**
	@brief Add a move that does not capture to the MoveList.
	@param pos The current board state.
	@param move The move to add.
	@return None
 */
	void addQuietMove(const Board& pos, Move&& move) noexcept;

/**
	@brief Add a move that does capture to the MoveList.
	@param pos The current board state.
	@param move The move to add.
	@return None
 */
	void addCaptureMove(const Board& pos, Move&& move) noexcept;

/**
	@brief Add a move that performs enPassant to the MoveList.
	@param pos The current board state.
	@param move The move to add.
	@return None
 */
	void addEnPasMove(const Board& pos, Move&& move) noexcept;

/**
	@brief Add a move that involves a pawn.
	@param pos The current board state.
	@param from The source square.
	@param to The destination square.
	@param side The side the pawn belongs to
	@return None
 */
	void addPawnMove(const Board& pos, uint32_t from, uint32_t to, uint32_t side) noexcept;
/**
	@brief Add a capture move that involves a pawn.
	@param pos The current board state.
	@param from The source square.
	@param to The destination square.
	@param cap The piece that was captured.
	@param side The side to move.
	@return None
 */
	void addPawnCaptureMove(const Board& pos, uint32_t from, uint32_t to, uint32_t cap, uint32_t side) noexcept;
/**
	@brief Add all Pawn moves to the MoveList.
	@param pos The current board state.
	@param side The side to move.
	@return None
 */
	void generatePawnMoves(const Board& pos, uint32_t side) noexcept;
/**
	@brief Add all Bishop moves to the MoveList.
	@param pos The current board state.
	@param side The side to move.
	@return None
 */
	void generateBishopMoves(const Board& pos, uint32_t side) noexcept;
/**
	@brief Add all Rook moves to the MoveList.
	@param pos The current board state.
	@param side The side to move.
	@return None
 */
	void generateRookMoves(const Board& pos, uint32_t side) noexcept;
/**
	@brief Add all Queen moves to the MoveList.
	@param pos The current board state.
	@param side The side to move.
	@return None
 */
	void generateQueenMoves(const Board& pos, uint32_t side) noexcept;
/**
	@brief Add all Knight moves to the MoveList.
	@param pos The current board state.
	@param side The side to move.
	@return None
 */
	void generateKnightMoves(const Board& pos, uint32_t side) noexcept;
/**
	@brief Add all King moves to the MoveList.
	@param pos The current board state.
	@param side The side to move.
	@return None
 */
	void generateKingMoves(const Board& pos, uint32_t side) noexcept;
/**
	@brief Add all Rook/Bishop/Queen moves to the MoveList.
	@param pos The current board state.
	@param side The side to move.
	@return None
 */
	void generateSlidingMoves(const Board& pos, uint32_t side) noexcept;
/**
	@brief Add all Knight/King moves to the MoveList.
	@param pos The current board state.
	@param side The side to move.
	@return None
 */
	void generateNonSlidingMoves(const Board& pos, uint32_t side) noexcept;
/**
	@brief Add all Castling moves to the MoveList.
	@param pos The current board state.
	@param side The side to move.
	@return None
 */
	void generateCastlingMoves(const Board& psd, uint32_t side) noexcept;

	static constexpr uint32_t kMaxPossibleMoves = 256;
	static constexpr uint32_t kCaptureBonus = 1000000;
	static constexpr uint32_t kPrimaryKillerBonus = 900000;
	static constexpr uint32_t kSecondaryKillerBonus = 800000;

	std::vector<Move> moves;

public:
	static constexpr uint32_t kPvMoveBonus = 2000000;
	
	MoveList() noexcept; 
	MoveList(const MoveList& o);
	MoveList(MoveList&& o) noexcept;

/**
	@brief Add all possible moves to the MoveList.
	@param pos The current board state.
	@return None
 */
	void generateAllMoves(const Board& pos) noexcept;
/**
	@brief Add all possible capture moves to the MoveList.
	@param pos The current board state.
	@return None
 */
	void generateAllCaptureMoves(const Board& pos) noexcept;
/**
	@brief Reorders the movelist to maximize alpha-beta hits.
	@param idx The index to start reordering the list at.
	@return None
 */
	void reorderList(int32_t idx) noexcept;
/**
	@brief Get the number of possible moves int he MoveList.
	@param None
	@return The size of the MoveList.
 */
	uint32_t size() const noexcept;
	
	const Move& operator[](const int idx) const noexcept;
	Move& operator[](const int idx) noexcept;
	// void printMoveList();
};


#endif
