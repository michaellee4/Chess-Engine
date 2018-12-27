#include "pvtable.h"
#include "defs.h"
#include "board.h"
#include "movemaker.h"
#include <utility>
/*** PV_ENTRY ***/

PV_Entry::PV_Entry(uint64_t key, Move _move) noexcept : pos_key(key), move(_move) {}

PV_Entry::PV_Entry(const PV_Entry& o) noexcept : pos_key(std::move(o.pos_key)), move(std::move(o.move)) {}

PV_Entry::PV_Entry(PV_Entry&& o) noexcept : pos_key(o.pos_key), move(o.move) {}

PV_Entry::PV_Entry() noexcept : pos_key(0ULL), move(NOMOVE) {}


/*** PV_Table ***/

PV_Table::PV_Table() noexcept : table() {}

Move PV_Table::get(const Board& pos) const noexcept
{
	uint64_t posKey = pos.pos_key;
	return this->table.at(posKey).move;
}

void PV_Table::insert(const Board& pos, const Move& move) noexcept
{
	uint64_t posKey = pos.pos_key;
	this->table[posKey] = PV_Entry(posKey, move);
}

int32_t PV_Table::size() const noexcept
{
	return this->table.size();
}

void PV_Table::clear() noexcept
{
	this->table.clear();
}

int32_t PV_Table::getPvLine(Board& pos, const uint32_t depth) noexcept
{
	ASSERT(depth < MAX_DEPTH);

	Move move = pos.pv_table.get(pos);
	uint32_t count = 0;

	while(!move.isNull() && count < depth)
	{
		ASSERT(count < MAX_DEPTH);
		// check move exists here?
		MM::makeMove(pos, move);
		pos.pv_arr[count++] = move;
		move = pos.pv_table.get(pos);
	}

	while(pos.ply > 0)
	{
		MM::takeMove(pos);
	}

	return count;
}

PV_Entry& PV_Entry::operator=(const PV_Entry& o) noexcept
{
	if(this != &o)
	{
		this->pos_key = o.pos_key;
		this->move = o.move;
	}
	return *this;
}

PV_Entry& PV_Entry::operator=(PV_Entry&& o) noexcept
{
	if(this != &o)
	{
		this->pos_key = std::move(o.pos_key);
		this->move = std::move(o.move);
	}
	return *this;
}