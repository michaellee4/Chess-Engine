/**
*	@file polyglot.h
*	@brief Contains declarations for the Polyglot Book class.
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef POLYGLOT_H
#define POLYGLOT_H
#include "constants.h"
#include <vector>

/**
 * This Struct represents how the polyglot entries are layed out in memory
 */
struct PolyglotEntry
{
	uint64_t key;
	uint16_t move;
	uint16_t weight;
	uint32_t learn;
};

/**
 * This class holds the in memory representation of the polyglot book 
 */
class PolyBook
{
private:
	/**
	 * Since the polyglot book uses different values for the pieces, this array provides a conversion
	 */
	static constexpr std::array<int32_t, 13> polyPiece { -1, 1, 3, 5, 7, 9, 11, 0, 2, 4, 6, 8, 10};
/**
	@brief Checks if enPassant is possible and there is a pawn in pace to perform the capture.
	@param pos The current board state.
	@return true if enPassant is possible with capture, false otherwise.
 */
	bool enPasPossible(const Board& pos);
/**
	@brief Generates the polyglot hashkey from the current board state.
	@param pos The current board state.
	@return The polyglot hashkey for a given board position.
 */
	uint64_t polyKeyFromBoard(const Board& pos);
/**
	@brief Returns the little-endian value of the big-endian input.
	@param bigEnd The bigEndian 16 bit number
	@return The little-endian value of the input number.
 */
	uint16_t endian_swap_u16(uint16_t bigEnd);
/**
	@brief Returns the little-endian value of the big-endian input.
	@param bigEnd The bigEndian 32 bit number
	@return The little-endian value of the input number.
 */
	uint32_t endian_swap_u32(uint32_t bigEnd);
/**
	@brief Returns the little-endian value of the big-endian input.
	@param bigEnd The bigEndian 64 bit number
	@return The little-endian value of the input number.
 */
	uint64_t endian_swap_u64(uint64_t bigEnd);

/**
	@brief Converts a polyglot move to the internal move representation.
	@param polyMove The book move in Polyglot form.
	@param pos The current board state
	@return The internal representation of the poly move.
 */
	Move convertPolyMove(uint16_t polyMove, const Board& pos);

	/**
	 * Provides a buffer to read in the polyglot entries
	 */	
	std::vector<PolyglotEntry> book;
public:
/**
	@brief Reads in from lib/polyglot-collection/Performance.bin.
	@param None
	@return true if the book was successfully read into memory, false otherwise.
 */
	bool readBook();

/**
	@brief Randomly returns one of the possible opening book moves for the given position.
	@param pos The current board state.
	@return A possible book move for the position.
 */
	Move getBookMove(Board& pos);

	PolyBook() noexcept;
};

#endif