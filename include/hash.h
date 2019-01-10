#ifndef HASH_H
#define HASH_H
#include "board.h"
#include "defs.h"
#include <array>

/**
 * This namespace provides various functions 
 * related to manipulating the board's hashkey
 */
namespace Hash
{
	/**
	 * Hashkey values 
	 */
	extern std::array<std::array<uint64_t, kBoardArraySize>, kNumPceTypes> PieceKeys;
	extern uint64_t SideKey;
	extern std::array<uint64_t, 16> CastleKeys;

	/**
	 * Input: Board Object
	 * Output: The position key for the given Board object
	 * Operation: Hashes in all pieces, enPas, side, and castle permissions
	 */
	uint64_t generatePosKey(const Board& pos);

	/**
	 * Input: A piece, locations, Board object
	 * Output: None
	 * Operation: Hashes in/out the piece on a given square
	 */
	inline void hashPce(uint32_t pce, uint32_t sq, Board& pos) noexcept
	{
		pos.pos_key ^= (PieceKeys[(pce)][(sq)]);
	}

	/**
	 * Input: Board object
	 * Output: None
	 * Operation: Hashes in/out the castle position
	 */
	inline void hashCa(Board& pos) noexcept
	{
		pos.pos_key ^= (CastleKeys[(pos.castle_perm)]);
	}

	/**
	 * Input: Board object
	 * Output: None
	 * Operation: Hashes in/out the side to move
	 */
	inline void hashSide(Board& pos) noexcept
	{
		pos.pos_key ^= (SideKey);
	}

	/**
	 * Input: Board object
	 * Output: None
	 * Operation: Hashes in/out the enPassant square
	 */
	inline void hashEP(Board& pos) noexcept
	{
		pos.pos_key ^= (PieceKeys[EMPTY][(pos.en_pas)]);
	}
}

#endif