#ifndef EVAL_H
#define EVAL_H
#include "board.h"
#include "defs.h"
namespace Value
{	
	constexpr int32_t kInfinity = 30000;

	constexpr int32_t kMateScore = 29000;
	
	constexpr std::array<int32_t, kChessboardSize> PawnTable {
		0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,
		10	,	10	,	0	,	-10	,	-10	,	0	,	10	,	10	,
		5	,	0	,	0	,	5	,	5	,	0	,	0	,	5	,
		0	,	0	,	10	,	20	,	20	,	10	,	0	,	0	,
		5	,	5	,	5	,	10	,	10	,	5	,	5	,	5	,
		10	,	10	,	10	,	20	,	20	,	10	,	10	,	10	,
		20	,	20	,	20	,	30	,	30	,	20	,	20	,	20	,
		0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	
	};

	constexpr std::array<int32_t, kChessboardSize> KnightTable {
		0	,	-10	,	0	,	0	,	0	,	0	,	-10	,	0	,
		0	,	0	,	0	,	5	,	5	,	0	,	0	,	0	,
		0	,	0	,	10	,	10	,	10	,	10	,	0	,	0	,
		0	,	0	,	10	,	20	,	20	,	10	,	5	,	0	,
		5	,	10	,	15	,	20	,	20	,	15	,	10	,	5	,
		5	,	10	,	10	,	20	,	20	,	10	,	10	,	5	,
		0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
		0	,	0	,	0	,	0	,	0	,	0	,	0	,	0		
	};

	constexpr std::array<int32_t, kChessboardSize> BishopTable {
		0	,	0	,	-10	,	0	,	0	,	-10	,	0	,	0	,
		0	,	0	,	0	,	10	,	10	,	0	,	0	,	0	,
		0	,	0	,	10	,	15	,	15	,	10	,	0	,	0	,
		0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,
		0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,
		0	,	0	,	10	,	15	,	15	,	10	,	0	,	0	,
		0	,	0	,	0	,	10	,	10	,	0	,	0	,	0	,
		0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	
	};

	constexpr std::array<int32_t, kChessboardSize> RookTable {
		0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
		0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
		0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
		0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
		0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
		0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
		25	,	25	,	25	,	25	,	25	,	25	,	25	,	25	,
		0	,	0	,	5	,	10	,	10	,	5	,	0	,	0		
	};

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

namespace EvalBB
{
	extern std::array<uint64_t, kNumFilesRanks> FileMask;
	extern std::array<uint64_t, kNumFilesRanks> RankMask;
	extern std::array<uint64_t, kChessboardSize> whitePassedMask;
	extern std::array<uint64_t, kChessboardSize> blackPassedMask;
	extern std::array<uint64_t, kChessboardSize> isolatedMask;
}


class Evaluator
{
	int32_t evalPawns(const Board& pos) noexcept;
	int32_t evalBishops(const Board& pos) noexcept;
	int32_t evalRooks(const Board& pos) noexcept;
	int32_t evalKnights(const Board& pos) noexcept;
public:
	int32_t evaluatePosition(const Board& pos) noexcept;
};

#endif