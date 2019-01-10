/**
*	@file hash.h
*	@brief Contains declarations of functions that manipulate the board position key
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef HASH_H
#define HASH_H
#include "board.h"
#include "constants.h"
#include <array>

/**
 * This namespace provides various functions 
 * related to manipulating the board's hashkey
 */
namespace Hash
{
	extern std::array<std::array<uint64_t, kBoardArraySize>, kNumPceTypes> PieceKeys;
	extern uint64_t SideKey;
	extern std::array<uint64_t, 16> CastleKeys;
/**
	@brief Gets the position hash key for the current position.
	@param pos The current board state.
	@return The 64 bit position key.
 */
	uint64_t generatePosKey(const Board& pos);

/**
	@brief Hashes in/out a piece on a given square.
	@param pce The piece to hash in/out.
	@param sq The square that the piece is/will be on
	@param pos The current board state
	@return None
 */
	inline void hashPce(uint32_t pce, uint32_t sq, Board& pos) noexcept
	{
		pos.pos_key ^= (PieceKeys[(pce)][(sq)]);
	}

/**
	@brief Hashes in/out the castle permissions.
	@param pos The current board state.
	@return None.
 */
	inline void hashCa(Board& pos) noexcept
	{
		pos.pos_key ^= (CastleKeys[(pos.castle_perm)]);
	}

/**
	@brief Hashes in/out the side to move.
	@param pos The current board state.
	@return None.
 */
	inline void hashSide(Board& pos) noexcept
	{
		pos.pos_key ^= (SideKey);
	}

/**
	@brief Hashes in/out the enPassant square.
	@param pos The current board state.
	@return None.
 */
	inline void hashEP(Board& pos) noexcept
	{
		pos.pos_key ^= (PieceKeys[EMPTY][(pos.en_pas)]);
	}
}

#endif