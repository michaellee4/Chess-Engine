/**
*	@file utils.h
*	@brief Contains declarations of functions that perform various miscellaneous actions in the engine.
*	@author Michael Lee
*	@date 1/9/2019
*/

#ifndef UTILS_H
#define UTILS_H

#include "defs.h"
#include "board.h"
#include "searchinfo.h"
#include "move.h"
#include <string>

namespace BoardUtils
{
	// *** initialized in init
	extern std::array<int32_t, kBoardArraySize> Sq120ToSq64;
	extern std::array<int32_t, kChessboardSize> Sq64ToSq120;
	extern std::array<int32_t, kBoardArraySize> FileBrd;
	extern std::array<int32_t, kBoardArraySize> RankBrd;
	/**
	* Gives the corresponding square to the Black side from the White side
 	*/
	constexpr std::array<int32_t, kChessboardSize> WhiteToBlack {
		56	,	57	,	58	,	59	,	60	,	61	,	62	,	63	,
		48	,	49	,	50	,	51	,	52	,	53	,	54	,	55	,
		40	,	41	,	42	,	43	,	44	,	45	,	46	,	47	,
		32	,	33	,	34	,	35	,	36	,	37	,	38	,	39	,
		24	,	25	,	26	,	27	,	28	,	29	,	30	,	31	,
		16	,	17	,	18	,	19	,	20	,	21	,	22	,	23	,
		8	,	9	,	10	,	11	,	12	,	13	,	14	,	15	,
		0	,	1	,	2	,	3	,	4	,	5	,	6	,	7
	};
}

/**
	@brief Checks if a square number in array-120 form is on the array-64 board representation.
	@param sq The square number in array-120 form.
	@return true if the square is on the array-64 board, false otherwise.
 */
bool sqOnBoard(uint32_t sq) noexcept;

/**
	@brief Gets the array-120 square number of a given file and rank number.
	@param file FILE_A <= file <= FILE_H
	@param rank RANK_1 <= rank <= RANK_8
	@return The array-120 square number of the given file and rank number
 */
int fileRankToSq(int32_t file, int32_t rank) noexcept;

/**
	@brief Generates a uniformally-distributed random 64-bit number.
	@param None
	@return A random 64 bit number
 */
uint64_t randU64() noexcept;

/**
	@brief Generates a uniformally-distributed random 64-bit number.
	@param piece A piece, OFFBOARD, EMPTY, or NO_SQ
	@return true if wP <= piece <= bK, false otherwise
 */
bool isPiece(int32_t piece) noexcept;
/**
	@brief Prints the 8x8 board with numbers indicating how many times each square is attacked by the provided side.
	@param side The attacking side
	@param pos The board state
	@return None
 */
void showAttackedSqs(const int side,Board& pos) noexcept;

/**
	@brief Returns the string representation of the square.
	@param sq A square in array-120 form.
	@return The string representation of the square (e.g "A1").
 */
std::string sqToString(const int sq) noexcept;

/**
	@brief Changes the given string to lowercase.
	@param str the string to change to lower.
	@return None
 */
void stringToLower(std::string& str) noexcept;

/**
	@brief Checks if the GUI interface has sent an interrrupt
	@param None
	@return true if there was a GUI interrupt, false otherwise.
 */
int InputWaiting();

/**
	@brief Reads in the GUI signal from stdin.
	@param info The engine's searchInfo instance
	@return None
 */
void ReadInput(SearchInfo& info);

#endif

