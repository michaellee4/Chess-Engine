/**
*	@file tester.h
*	@brief Contains declarations of functions used for Perft testing for testing accuracy of move generation and move making.
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef PERFT_H
#define PERFT_H

#include "board.h"
#include <string>

class PerftTester
{
private:
	const uint32_t depth_limit = 6;
	uint64_t leafNodes;
/**
	@brief Recursive helper method that backtracks through all possible moves and counts the number of leaf nodes (final positions) reached.
	@param depth Current search depth.
	@param pos The current board state.
	@return None
 */
	void perft(uint32_t depth, Board& pos) noexcept;
public:
/**
	Calls the perft helper function to count number of leaf nodes reached. If print is enabled then the engine will also output the time taken and total number of positions reached from each possible initial move from the starting position
	@param depth Desired search depth.
	@param pos The current board state.
	@param print Print enabled
	@return Total number of leaf nodes reached
 */
	int perftTest(uint32_t depth, Board& pos, bool print) noexcept;
/**
	Loops through all provided positions in the perftsuite.epd file and automatically performs a perft test to depth 5 (depth 6 takes too long for some positions) and verifies the results with the provided number in the file.	@param depth Desired search depth.
	@param pos The current board state.
	@return None
 */
	void perftTestAll(Board& pos) noexcept;
	
	PerftTester() noexcept;
};


#endif
