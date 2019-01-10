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
 * Input: A square in array-120 format
 * Output: true if the square is on the board in array-120 format, false otherwise
 * Operation: None
 */
bool sqOnBoard(uint32_t sq) noexcept;

/**
 * Input: A file and rank (e.g A1)
 * Output: the square number of the file/rank in array-120 form
 * Operation: None
 */
int fileRankToSq(int file, int rank) noexcept;

/**
 * Input: None
 * Output: A random 64 bit number
 * Operation: Uses the standard uniform distribution generator to generate the number
 * credits to //https://stackoverflow.com/questions/37396278/how-to-generate-very-large-random-number-in-c
 */
uint64_t randU64() noexcept;

/**
 * Input: an integer
 * Output: true if the number is a piece within the range of the piece enum
 * Operation: None
 */
bool isPiece(int piece) noexcept;

/**
 * Input: None
 * Output: Prints the 8x8 board with numbers indicating how many 
 *		   times each square is attacked by the provided side
 * Operation: None
 */
void showAttackedSqs(const int side,Board& pos) noexcept;

/**
 * Input: An integer
 * Output: The string representation of the square (e.g "A1")
 * Operation: None
 */
std::string sqToString(const int sq) noexcept;

/**
 * Input: A string
 * Output: None
 * Operation: Changes the underlying string to lowercase
 */
void stringToLower(std::string& str) noexcept;

/**
 * Input: None
 * Output: true(1) if the gui interface is attempting to send input to the engine, false(0) otherwise 
 * Credits to the olithink chess engine for the code
 */
int InputWaiting();

/**
 * Input: SearchInfo object
 * Output: None
 * Operation: updates the SearchInfo object if input was detected
 * Credits to the olithink chess engine for the code
 */
void ReadInput(SearchInfo& info);

#endif

