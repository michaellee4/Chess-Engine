#include "pvtable.h"
#include "defs.h"
#include "board.h"
#include "movemaker.h"
#include "utils.h"
#include "eval.h"
#include <utility>

/*** PV_ENTRY ***/
PvEntry::PvEntry(uint64_t key, Move _move) noexcept : pos_key(key), move(std::move(std::move(_move))), score(0), depth(0), flags(0) {}

PvEntry::PvEntry(const PvEntry& o) noexcept  = default;

PvEntry::PvEntry(PvEntry&& o) noexcept : pos_key(o.pos_key), move(std::move(o.move)), score(o.score), depth(o.depth), flags(o.flags) {}

PvEntry::PvEntry() noexcept : pos_key(0ULL), move(NOMOVE), score(0), depth(0), flags(0) {}

PvEntry::PvEntry(uint64_t key, Move _move, int32_t _score, int32_t _depth, int32_t _flags) noexcept : pos_key(key), move(std::move(std::move(_move))), score(_score), depth(_depth), flags(_flags) {}

PvEntry& PvEntry::operator=(const PvEntry& o) noexcept
{
	if(this != &o)
	{
		this->pos_key = o.pos_key;
		this->move = o.move;
		this->score = o.score;
		this->depth = o.depth;
		this->flags = o.flags;
	}
	return *this;
}

PvEntry& PvEntry::operator=(PvEntry&& o) noexcept
{
	if(this != &o)
	{
		this->pos_key = o.pos_key;
		this->move = std::move(o.move);
		this->score = o.score;
		this->depth = o.depth;
		this->flags = o.flags;
	}
	return *this;
}

/*** PvTable ***/
PvTable::PvTable() noexcept : pv_table(), pv_arr(kMaxSearchDepth) 
{
	pv_table.reserve(125000);
}

Move PvTable::get(const Board& pos) noexcept
{
	uint64_t posKey = pos.pos_key;
	return this->pv_table[posKey].move;
}

void PvTable::insert(const Board& pos, const Move& move) noexcept
{
	uint64_t posKey = pos.pos_key;
	this->pv_table[posKey] = PvEntry(posKey, move);
}

void PvTable::insert(const Board& pos, const Move& move, int32_t score, int32_t depth, int32_t flags) noexcept
{
	uint64_t posKey = pos.pos_key;
	if(score > Value::kInfinity - static_cast<int32_t>(kMaxSearchDepth)) 
	{ 
		score += pos.ply;
	} 
	else if (score < -(Value::kInfinity - static_cast<int32_t>(kMaxSearchDepth))) 
	{
		score -= pos.ply;
	}
	this->pv_table[posKey] = PvEntry(posKey, move, score, depth, flags);
}

int32_t PvTable::size() const noexcept
{
	return this->pv_table.size();
}

void PvTable::clear() noexcept
{
	this->pv_table.clear();
}

int32_t PvTable::getPvLine(Board& pos, const uint32_t depth) noexcept
{
	Move move = this->get(pos);
	uint32_t count = 0;
	while(!move.isNull() && count < depth)
	{
		// check move exists here?
		MM::makeMove(pos, move);
		this->pv_arr[count++] = move;	
		move = this->get(pos);
	}
	while(pos.ply > 0)
	{
		MM::takeMove(pos);
	}
	return count;
}

bool PvTable::getHashEntry(Board& pos, Move& pvMove,int32_t& score,int32_t alpha,int32_t beta, int32_t depth) noexcept
{
	uint64_t posKey = pos.pos_key;
	if(this->pv_table.find(posKey) != this->pv_table.end())
	{
		PvEntry& posEntry = this->pv_table.at(posKey);
		pvMove = posEntry.move;
		if(posEntry.depth >= depth)
		{
			score = posEntry.score;
			if(score > Value::kInfinity - static_cast<int32_t>(kMaxSearchDepth)) 
			{ 
				score -= pos.ply;
			} 
			else if (score < -(Value::kInfinity - static_cast<int32_t>(kMaxSearchDepth))) 
			{
					score += pos.ply;
			}
			if(posEntry.flags == HFALPHA)
			{
				if(score <= alpha)
				{
					score = alpha;
					return true;
				}
			}
			else if (posEntry.flags == HFBETA)
			{
				if(score >= beta)
				{
					score = beta;
					return true;
				}
			}
			else if (posEntry.flags == HFEXACT)
			{
				return true;
			}
		}
	}
	return false;
}
