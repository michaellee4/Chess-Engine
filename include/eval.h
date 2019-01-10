/**
*	@file eval.h
*	@brief Contains declarations of functions that determine the strength of a given position.
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef EVAL_H
#define EVAL_H
#include "board.h"
#include "pieceinfo.h"
#include "constants.h"

/**
	@brief Provides several constant values used for evaluating the board state.
 */
namespace Value
{	
/**
	@brief Highest possible score
 */
	constexpr int32_t kInfinity = 30000;

/**
	@brief Score for a Checkmate
 */
	constexpr int32_t kMateScore = 29000;

/**
	@brief Score bonus for isolated pawns (no same color pawn on adjacent files)
 */
	constexpr int32_t kIsolatedPawn = -10;

/**
	@brief Score bonus for a Rook on an open file (no pawns)
 */
	constexpr int32_t kOpenRookFile = 10;
/**
	@brief Score bonus for a Rook on a semi-open file (no same color pawn)
 */
	constexpr int32_t kSemiOpenRookFile = 5;
/**
	@brief Score bonus for a Queen on an open file (no pawns)
 */
	constexpr int32_t kOpenQueenFile = 5;

/**
	@brief Score bonus for a Queen on a semi-open file (no same color pawn)
 */
	constexpr int32_t kSemiOpenQueenFile = 3;

/**
	@brief Material threshold to determine when the endgame starts
 */
	constexpr int32_t kEndGameThreshold = PieceInfo::PieceVal[wR] + 2 * PieceInfo::PieceVal[wB] + 2 * PieceInfo::PieceVal[wP];

/**
	@brief Score bonus for the Bishop pair
 */
	constexpr int32_t kBishopPair = 30;

/**
	@brief Score bonus for Passed pawns based on distance
 */
	constexpr std::array< int32_t, kNumFilesRanks> passedPawnScore {0, 5, 10, 20, 35, 60, 100, 200};

/**
	@brief Scores the position of the Pawns
 */
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

/**
	@brief Scores the position of the Knights
 */
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

/**
	@brief Scores the position of the Bishops
 */
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

/**
	@brief Scores the position of the Rooks
 */
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
/**
	@brief Scores the king in the late game. Prioritizes the center
 */
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

/**
	@brief Scores the king for the earlygame. Prioritizes staying safe
 */
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
/**
	@brief Evaluates the strength of the Pawns.
	@param pos The current board state.
	@return The score attributed to the Pawns.
 */
	int32_t evalPawns(const Board& pos) noexcept;
/**
	@brief Evaluates the strength of the Bishop.
	@param pos The current board state.
	@return The score attributed to the Bishop.
 */
	int32_t evalBishops(const Board& pos) noexcept;
/**
	@brief Evaluates the strength of the Rook.
	@param pos The current board state.
	@return The score attributed to the Rook.
 */
	int32_t evalRooks(const Board& pos) noexcept;
/**
	@brief Evaluates the strength of the Knights.
	@param pos The current board state.
	@return The score attributed to the Knights.
 */
	int32_t evalKnights(const Board& pos) noexcept;
/**
	@brief Evaluates the strength of the Queens.
	@param pos The current board state.
	@return The score attributed to the Queens.
 */
	int32_t evalQueens(const Board& pos) noexcept;
/**
	@brief Evaluates the strength of the Kings.
	@param pos The current board state.
	@return The score attributed to the Kings.
 */
	int32_t evalKings(const Board& pos) noexcept;
/**
	@brief Determines if there is enough material to end in checkmate.
	@param pos The current board state.
	@return true if there is enough material on either side to lead to checkmate, false otherwise.
 */
	bool drawnMaterial(const Board& pos) noexcept;
public:
/**
	@brief Evaluates the score for the current board position for the side to move.
	@param pos The current board state.
	@return The overall score of the position
 */
	int32_t evaluatePosition(const Board& pos) noexcept;
};

#endif