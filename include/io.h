#ifndef IO_H
#define IO_H

#include "board.h"
#include "move.h"
#include "movelist.h"
#include "searchinfo.h"
#include <string>

/**
 * This namespace provides several methods to print the various Engine data structures
 */
namespace IO
{
	/**
	 * Dictionaries to provide string representations of pieces/sides/ranks/files/enPassant sq's
	 */
	const std::string PceChar = ".PNBRQKpnbrqk";
	const std::string SideChar = "wb-";
	const std::string RankChar = "12345678";
	const std::string FileChar = "abcdefgh";
	const std::unordered_map<uint32_t, std::string> epstr = 
	{{71,"a6"}, {72,"b6"}, {73,"c6"}, {74,"d6"}, {75,"e6"}, {76,"f6"}, {77,"g6"}, {78,"h6"},
	 {41,"a3"}, {42,"b3"}, {43,"c3"}, {44,"d3"}, {45,"e3"}, {46,"f3"}, {47,"g3"}, {48,"h3"}, {99, "None"}};

	void printBoard(const Board& pos) noexcept;
	void printBitBoard(const uint64_t) noexcept;
	void printMoveList(const MoveList& list) noexcept;
	void printSearchDetails(const SearchInfo& info, int32_t curDepth, int32_t bestScore, PV_Table& pv, int32_t pvMoves) noexcept;
	void printBestMove(Board& pos, const SearchInfo& info, const Move& bestMove) noexcept;
	Move parseMove(std::string input, const Board& pos) noexcept;
}

#endif
