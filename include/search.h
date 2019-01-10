#ifndef SEARCH_H
#define SEARCH_H
#include "defs.h"
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
	 * bitmask to check search flags every 2048 positions
	 */
	static constexpr uint32_t kInterval = 0x7FF;

	/**
	 * Input: None
	 * Output: true if current position has happened in the last 50 moves
	 * 		   false otherwise
	 * Operation: None
	 */
	int32_t isRepetition(const Board& pos) noexcept;

	/**
	 * Input: None
	 * Output: None
	 * Operation: Starts the game loop
	 */
	void checkStop(SearchInfo& info);

	/**
	 * Input: Board object, SearchInfo object
	 * Output: None
	 * Operation: Clears the board's search_hist and search_killers vectors
	 */
	void clearForSearch(Board& pos, SearchInfo& info) noexcept;

	/**
	 * Input: alpha cutoff, beta cutoff, search depth, Board object, Searchinfo object, Null move flag
	 * Output: score of the current position
	 * Operation: Recursively performs the mini-max algorithm with alpha-beta pruning
	 * 			  If doNull is set, considers making a null move to improve search time
	 */
	int32_t alphaBeta(int32_t alpha, int32_t beta, uint32_t depth, Board& pos, SearchInfo& info, bool doNull) noexcept;

	/**
	 * Input: alpha cutoff, beta cutoff, search depth, Board object, Searchinfo object
	 * Output: score of the current position
	 * Operation: Searches similarly to alpha-beta but only on capture moves
	 * 			  Used to avoid the horizon effect.
	 */
	int32_t quiescenceSearch(int32_t alpha, int32_t beta, Board& pos, SearchInfo& info) noexcept;

	/**
	 * Input: Board object
	 * Output: true if the position has been repeated 3 times before, false otherwise
	 * Operation: None
	 */
	bool threeFoldRepetition(const Board& pos) noexcept;

	/**
	 * Input: Board object
	 * Output: True if there is sufficient material on either side to checkmate assuming perfect play
	 * Operation: None
	 */
	bool drawnMaterial(const Board& pos) noexcept;
public:
	Evaluator eval;
	PV_Table pv;

	/**
	 * Input: Board object, Searchinfo object
	 * Output: Prints out the search line and best move to the console
	 * Operation: Performs iterative deepening alpha-beta search on the given position
	 */
	void searchPosition(Board& pos, SearchInfo& info) noexcept;

	/**
	 * Input: Board object
	 * Output: true if 3-fold repetition, 50 move rule, checkmate, stalemate, or insufficent material has occurred, false otherwise
	 * Operation: None
	 */
	bool isGameOver(Board& pos) noexcept;

	SearchAgent() noexcept;
};

#endif