/**
*	@file pvtable.h
*	@brief Contains declarations for the transposition table class used for caching.
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef PVTABLE_H
#define PVTABLE_H

#include "move.h"
#include <unordered_map>
#include <vector>

class Board;
/**
 * This class holds the cached info of our searches for use with the PVTable
 */
class PvEntry
{
public:
	uint64_t pos_key;
	Move move;
	int32_t score;
	int32_t depth;
	int32_t flags;
	PvEntry(uint64_t key, Move _move, int32_t _score, int32_t _depth, int32_t _flags) noexcept;
	PvEntry(uint64_t key, Move move) noexcept;
	PvEntry(const PvEntry& o) noexcept;
	PvEntry(PvEntry&& o) noexcept;
	PvEntry() noexcept;

	PvEntry& operator=(const PvEntry& o) noexcept;
	PvEntry& operator=(PvEntry&& o) noexcept;
};

/**
 * This class holds all info for a given position with the best move found. 
 * Serves as a cache to improve evaluation speed. Also called a transposition table.
 */
class PvTable
{
private:
	std::unordered_map<uint64_t, PvEntry> pv_table;
public:
	std::vector<Move> pv_arr;

	PvTable() noexcept;
/**
	@brief Get the best move previously found for this position.
	@param pos The current board state.
	@return The best move previously found for this position.
 */
	Move get(const Board& pos) noexcept;

/**
	@brief Stashes the move associated with this position into the hash map.
	@param pos The current board state.
	@param move The move to store for this position.
	@return None
 */
	void insert(const Board& pos, const Move& move) noexcept;

/**
	@brief Stashes the move associated with this position into the hash map.
	@param pos The current board state.
	@param move The move to store for this position.
	@param score The evaluation of this position.
	@param depth The depth that this position was previously searched to.
	@param flags The flags that are associated with the move.
	@return None
 */
	void insert(const Board& pos, const Move& move, int32_t score, int32_t depth, int32_t flags) noexcept;

/**
	@brief Gets the number of entries in the transposition table.
	@param None
	@return The number of entries in the transposition table.
 */
	int32_t size() const noexcept;

/**
	@brief Clears all entries in the transposition table.
	@param None
	@return None
 */
	void clear() noexcept;

/**
	@brief Fills in the pv array with the searched pv moves and returns the length of the line.
	@param pos The current board state.
	@param depth The search depth.
	@return The number of moves in the Pv line
 */
	int32_t getPvLine(Board& pos, const uint32_t depth) noexcept;

/**
	@brief Checks the alpha beta bounds and returns if a better, previously cached move is found.
	@param pos The current board state.
	@param pvMove The move to store the found move in if found.
	@param score The score buffer to store the found score in if found
	@param alpha The alpha cutoff
	@param beta The beta cutoff
	@param depth The desired search depth
	@return true if the position has an applicable cached move.
 */
	bool getHashEntry(Board& pos,Move& pvMove,int32_t& score,int32_t alpha,int32_t beta, int32_t depth) noexcept;
};


#endif
