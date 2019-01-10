#ifndef PERFT_H
#define PERFT_H

#include "board.h"
#include <string>

/**
 * This class has various methods to 
 * count the total number of final positions
 * reached at each depth of search and 
 * uses the perftsuite.epd file to verify
 * the results.
 * 
 * Primarily tests the accuracy of move
 * generation and move making.
 */
class PerftTester
{
private:
	const uint32_t depth_limit = 6;
	uint64_t leafNodes;
	/**
	 * Input: Search depth, Board object
	 * Output: None
	 * Operation: Recursive helper method that backtracks through
	 *			  all possible moves and counts the number
	 *			  of leaf nodes (final positions) reached
	 */
	void perft(uint32_t depth, Board& pos) noexcept;
public:
	/**
	 * Input: Search depth, Board object, print flag
	 * Output: Total number of final positions reached
	 * Operation: Calls the perft helper function to count
	 *			  number of leaf nodes reached. 
	 *			  If print is enabled then the engine will also
	 *			  output the time taken and total number of positions
	 *			  reached from each possible initial move from the 
	 *			  starting position
	 */
	int perftTest(uint32_t depth, Board& pos, bool print) noexcept;

	/**
	 * Input: Board object
	 * Output: None
	 * Operation: Loops through all provided positions in the perftsuite.epd file
	 *			  and automatically performs a perft test to depth 5 (depth 6 takes too long for some positions)
	 *			  and verifies the results with the provided number in the file.
	 */
	void perftTestAll(Board& pos) noexcept;
	
	PerftTester() noexcept;
};


#endif
