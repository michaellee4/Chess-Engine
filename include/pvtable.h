#ifndef PVTABLE_H
#define PVTABLE_H

#include <unordered_map>
#include "move.h"
class Board;
class PV_Entry
{
	public:
		uint64_t pos_key;
		Move move;
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
		std::unordered_map<uint64_t, PV_Entry> table;
	public:
		PV_Table() noexcept;
		Move get(const Board& pos) noexcept;
		void insert(const Board& pos, const Move& move) noexcept;
		int32_t size() const noexcept;
		void clear() noexcept;
		static int32_t getPvLine(Board& pos, const uint32_t depth) noexcept;
};


#endif
