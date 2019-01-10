#ifndef PVTABLE_H
#define PVTABLE_H

#include "move.h"
#include <unordered_map>
#include <vector>

class Board;
/**
 * This class holds the cached info of our searches for use with the PVTable
 */
class PV_Entry
{
	public:
		uint64_t pos_key;
		Move move;
		int32_t score;
		int32_t depth;
		int32_t flags;
		PV_Entry(uint64_t key, Move _move, int32_t _score, int32_t _depth, int32_t _flags) noexcept;
		PV_Entry(uint64_t key, Move move) noexcept;
		PV_Entry(const PV_Entry& o) noexcept;
		PV_Entry(PV_Entry&& o) noexcept;
		PV_Entry() noexcept;

		PV_Entry& operator=(const PV_Entry& o) noexcept;
		PV_Entry& operator=(PV_Entry&& o) noexcept;
};

class PV_Table
{
	private:
		std::unordered_map<uint64_t, PV_Entry> pv_table;
	public:
		std::vector<Move> pv_arr;
		PV_Table() noexcept;
		Move get(const Board& pos) noexcept;
		void insert(const Board& pos, const Move& move) noexcept;
		void insert(const Board& pos, const Move& move, int32_t score, int32_t depth, int32_t flags) noexcept;
		int32_t size() const noexcept;
		void clear() noexcept;
		int32_t getPvLine(Board& pos, const uint32_t depth) noexcept;
		bool getHashEntry(Board& pos,Move& pvMove,int32_t& score,int32_t alpha,int32_t beta, int32_t depth) noexcept;
};


#endif
