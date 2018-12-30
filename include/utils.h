#ifndef UTILS_H
#define UTILS_H

#include "defs.h"
#include "board.h"
#include "searchinfo.h"
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

bool sqOnBoard(uint32_t sq) noexcept;

// returns the SQ# on the 120 Sq board representation
int fileRankToSq(int file, int rank) noexcept;

// generates a random 64 bit integer
uint64_t randU64() noexcept;

bool isPiece(int piece) noexcept;

// prints the 8x8 board with numbers indicating how many times each sq is attacked by the provided side
void showAttackedSqs(const int side,Board& pos) noexcept;

// String representation of a square
std::string sqToString(const int sq) noexcept;

void stringToLower(std::string& str) noexcept;

int InputWaiting();

void ReadInput(SearchInfo& info);

#endif

