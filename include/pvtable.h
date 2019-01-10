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
		 * Input: Board object
		 * Output: the best move previously found for this position
		 * Operation: None
		 */
		Move get(const Board& pos) noexcept;

		/**
		 * Input: Board object, move, and optional flags
		 * Output: None
		 * Operation: Stashes the move associated with this position into the hash map
		 */
		void insert(const Board& pos, const Move& move) noexcept;
		void insert(const Board& pos, const Move& move, int32_t score, int32_t depth, int32_t flags) noexcept;
		/**
		 * Input: None
		 * Output: The number of entries in the transposition table
		 * Operation: None
		 */
		int32_t size() const noexcept;

		/**
		 * Input: None
		 * Output: None
		 * Operation: Clears all entries in the transposition table
		 */
		void clear() noexcept;

		/**
		 * Input: Board object, search depth
		 * Output: The length of the current pvLine
		 * Operation: Fills in the pv array with the searched pv moves
		 */
		int32_t getPvLine(Board& pos, const uint32_t depth) noexcept;

		/**
		 * Input: Board object, move, alpha beta info
		 * Output: true if position has an applicable cached move
		 * Operation: Checks the alpha beta bounds and returns if a better cached move is found
		 */
		bool getHashEntry(Board& pos,Move& pvMove,int32_t& score,int32_t alpha,int32_t beta, int32_t depth) noexcept;
};


#endif
