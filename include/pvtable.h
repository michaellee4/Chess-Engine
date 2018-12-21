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
		PV_Entry(uint64_t key, Move move);
		PV_Entry();
};

class PV_Table
{
	private:
	public:
		std::unordered_map<uint64_t, PV_Entry> table;
		PV_Table();
		Move get(const Board& pos);
		void insert(const Board& pos, const Move& move);
		int32_t size();
		void clear();
		static int32_t getPvLine(Board& pos, const uint32_t depth);
};


#endif
