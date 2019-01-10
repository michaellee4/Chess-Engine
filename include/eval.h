/**
*	@file eval.h
*	@brief Contains declarations of functions that determine the strength of a given position.
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef EVAL_H
#define EVAL_H
#include "board.h"
#include "defs.h"
namespace Value
{	
	constexpr int32_t kInfinity = 30000;

	constexpr int32_t kMateScore = 29000;

	constexpr int32_t kIsolatedPawn = -10;

	constexpr int32_t kOpenRookFile = 10;

	constexpr int32_t kSemiOpenRookFile = 5;

	constexpr int32_t kOpenQueenFile = 5;

	constexpr int32_t kSemiOpenQueenFile = 3;

	constexpr int32_t kEndGameThreshold = PieceInfo::PieceVal[wR] + 2 * PieceInfo::PieceVal[wB] + 2 * PieceInfo::PieceVal[wP];

	constexpr int32_t kBishopPair = 30;

	//passed pawn score based on rank
	constexpr std::array< int32_t, kNumFilesRanks> passedPawnScore {0, 5, 10, 20, 35, 60, 100, 200};

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

	constexpr std::array<int32_t, kChessboardSize> KingEndGame = {	
		-50	,	-10	,	0	,	0	,	0	,	0	,	-10	,	-50	,
		-10,	0	,	10	,	10	,	10	,	10	,	0	,	-10	,
		0	,	10	,	15	,	15	,	15	,	15	,	10	,	0	,
		0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,
		0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,
		0	,	10	,	15	,	15	,	15	,	15	,	10	,	0	,
		-10,	0	,	10	,	10	,	10	,	10	,	0	,	-10	,
		-50	,	-10	,	0	,	0	,	0	,	0	,	-10	,	-50	
	};

	constexpr std::array<int32_t, kChessboardSize> KingOpening = {	
		0	,	5	,	5	,	-10	,	-10	,	0	,	10	,	5	,
		-30	,	-30	,	-30	,	-30	,	-30	,	-30	,	-30	,	-30	,
		-50	,	-50	,	-50	,	-50	,	-50	,	-50	,	-50	,	-50	,
		-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,
		-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,
		-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,
		-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,
		-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70		
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
	int32_t evalQueens(const Board& pos) noexcept;
	int32_t evalKings(const Board& pos) noexcept;
	bool drawnMaterial(const Board& pos) noexcept;
public:
	int32_t evaluatePosition(const Board& pos) noexcept;
};

#endif