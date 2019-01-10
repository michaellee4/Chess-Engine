#ifndef POLYGLOT_H
#define POLYGLOT_H
#include "defs.h"
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
	 * Input: Board object
	 * Output: true if enPassant is possible and there is a pawn in place to perform the capture, false otherwise
	 * Operation: None
	 */
	bool enPasPossible(const Board& pos);

	/**
	 * Input: Board object
	 * Output: The polyglot hashkey for a given board position
	 * Operation: Looks up the array in the polykeys.h array
	 */
	uint64_t polyKeyFromBoard(const Board& pos);

	/**
	 * Input: 16, 32, or 64 bit big-endian number
	 * Output: little endian value of the given number
	 * Operation: required since the polyglot book stores entries in big-endian
	 */
	uint16_t endian_swap_u16(uint16_t);
	uint32_t endian_swap_u32(uint32_t);
	uint64_t endian_swap_u64(uint64_t);

	/**
	 * Input: 16 bit polyglot move, Board object
	 * Output: internal move object
	 * Operation: converts a polyglot move to the internal move representation
	 */
	Move convertPolyMove(uint16_t polyMove, const Board& pos);

	/**
	 * Provides a buffer to read in the polyglot entries
	 */	
	std::vector<PolyglotEntry> book;
public:

	/**
	 * Input: None
	 * Output: true if book was successfully read into memory, false otherwise
	 * Operation: Reads in from lib/polyglot-collection/Performance.bin
	 */	
	bool readBook();

	/**
	 * Input: Board object
	 * Output: randomly returns one of the possible opening book moves for the given position
	 * Operation: None
	 */
	Move getBookMove(Board& pos);

	PolyBook() noexcept;
};

#endif