/**
*	@file search.h
*	@brief Contains declarations of functions to search through the board state.
*	@author Michael Lee
*	@date 1/9/2019
*/

#ifndef SEARCH_H
#define SEARCH_H
#include "constants.h"
#include "board.h"
#include "searchinfo.h"
#include "eval.h"
#include "polyglot.h"
#include "pvtable.h"

/**
 * This class provides functions to search through the board state
 */
class SearchAgent
{
private:
	/**
	 * Bitmask to check search flags every 2048 positions
	 */
	static constexpr uint32_t kInterval = 0x7FF;
/**
	@brief Checks if the position has happened before.
	@param pos The current board state.
	@return true if the current position has happened before, false otherwise
 */
	int32_t isRepetition(const Board& pos) noexcept;
/**
	@brief Checks if the time limit has been passed.
	@param None
	@return None
 */
	void checkStop(SearchInfo& info);
/**
	@brief Clears the board's search_hist and search_killers vectors.
	@param pos The current board state.
	@param info The engine's searchInfo object.
	@return None
 */
	void clearForSearch(Board& pos, SearchInfo& info) noexcept;
/**
	@brief Recursively performs the mini-max algorithm with alpha-beta pruning. If doNull is set, considers making a null move to improve search time	@param pos The current board state.
	@param alpha The alpha cutoff
	@param beta The beta cutoff
	@param depth The current depth of the search
	@param pos The current board state
	@param info The engine's searchInfo object
	@param doNull Null move flag
	@return The evaluation of the current position
 */
	int32_t alphaBeta(int32_t alpha, int32_t beta, uint32_t depth, Board& pos, SearchInfo& info, bool doNull) noexcept;
/**
	@brief Searches similarly to alpha-beta but only on capture moves. Used to avoid the horizon effect.	
	@param alpha The alpha cutoff
	@param beta The beta cutoff
	@param pos The current board state
	@param info The engine's searchInfo object
	@return The evaluation of the current position
 */
	int32_t quiescenceSearch(int32_t alpha, int32_t beta, Board& pos, SearchInfo& info) noexcept;

/**
	@brief Checks if threefold repetition has occurred	
	@param pos The current board state
	@return true if threefold repetition has occurred, false otherwise.
 */
	bool threeFoldRepetition(const Board& pos) noexcept;
/**
	@brief Checks if there is sufficient material to checkmate either side.
	@param pos The current board state
	@return true if there is sufficient material on either side to cause checkmate.
 */
	bool drawnMaterial(const Board& pos) noexcept;
public:
	Evaluator eval;
	PvTable pv;
/**
	@brief Depth reduction value used in null move pruning
 */
	static constexpr int32_t R = 4;
/**
	@brief Performs iterative deepening alpha-beta search on the position.
	@param pos The current board state
	@param info The engine's searchInfo object
	@return None
 */
	void searchPosition(Board& pos, SearchInfo& info) noexcept;

/**
	@brief Checks if there is checkmate, stalemate, insufficient material, or threefold repetition.	
	@param pos The current board state
	@return true if the game has concluded in one way or other, false otherwise
 */
	bool isGameOver(Board& pos) noexcept;

	SearchAgent() noexcept;
};

#endif