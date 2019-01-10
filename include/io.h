/**
*	@file io.h
*	@brief Contains declarations of functions that print the various Engine data structures
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef IO_H
#define IO_H

#include "board.h"
#include "move.h"
#include "movelist.h"
#include "searchinfo.h"
#include <string>

/**
	@brief Various functions to print out engine data structures
 */
namespace IO
{
	/**
	 * Dictionary to provide string representations of piecess
	 */
	const std::string PceChar = ".PNBRQKpnbrqk";
	/**
	 * Dictionary to provide string representations of sides
	 */
	const std::string SideChar = "wb-";
	/**
	 * Dictionary to provide string representations of ranks
	 */
	const std::string RankChar = "12345678";
	/**
	 * Dictionary to provide string representations of files
	 */
	const std::string FileChar = "abcdefgh";
	/**
	 * Dictionary to provide string representations of enPassant sq's
	 */
	const std::unordered_map<uint32_t, std::string> epstr = 
	{{71,"a6"}, {72,"b6"}, {73,"c6"}, {74,"d6"}, {75,"e6"}, {76,"f6"}, {77,"g6"}, {78,"h6"},
	 {41,"a3"}, {42,"b3"}, {43,"c3"}, {44,"d3"}, {45,"e3"}, {46,"f3"}, {47,"g3"}, {48,"h3"}, {99, "None"}};

/**
	@brief Prints out the board to stdio.
	@param pos The current board state.
	@return None.
 */
	void printBoard(const Board& pos) noexcept;

/**
	@brief Prints out the bitboard to stdio.
	@param bb The bitboard to print.
	@return None.
 */
	void printBitBoard(const uint64_t bb) noexcept;

/**
	@brief Prints out the MoveList to stdio.
	@param list The MoveList to print.
	@return None.
 */
	void printMoveList(const MoveList& list) noexcept;

/**
	@brief Prints out the search details to stdio.
	@param info The engine's searchInfo struct
	@param curDepth The current search depth.
	@param bestScore The evaluation of the current board state
	@param pv The transposition table.
	@param pvMoves The length of the Pv line
	@param pos The current board state.
	@return None.
 */
	void printSearchDetails(const SearchInfo& info, int32_t curDepth, int32_t bestScore, PvTable& pv, int32_t pvMoves) noexcept;

/**
	@brief Prints out the best move stdio for the protocol manager.
	@param pos The current board state.
	@param info The engine's searchInfo struct.
	@param bestMove The best move that was found.
	@return None.
 */
	void printBestMove(Board& pos, const SearchInfo& info, const Move& bestMove) noexcept;

/**
	@brief Reads in a move string and converts it to the internal representation.
	@param input The move that was read in (e.g e2e4).
	@param pos The current board state.
	@return The internal representation of the input move.
 */
	Move parseMove(std::string input, const Board& pos) noexcept;
}

#endif
