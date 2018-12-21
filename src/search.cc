#include "search.h"

int32_t SearchAgent::isRepetition(const Board& pos)
{
	for(int32_t idx = pos.hist_ply - pos.fifty_move; idx < pos.hist_ply - 1; ++idx)
	{
		ASSERT(idx >= 0 && (unsigned)idx < MAX_GAME_MOVES);
		if(pos.pos_key == pos.history[idx].pos_key)
			return true;
	}
	return false;
}

void SearchAgent::checkStop()
{

}

void SearchAgent::clearForSearch(SearchInfo& info)
{

}

int32_t SearchAgent::alphaBeta(int32_t alpha, int32_t beta, uint32_t depth, SearchInfo& info, bool doNull)
{
	return 0;
}

int32_t SearchAgent::quiescenceSearch(int32_t alpha, int32_t beta, Board& pos, SearchInfo& info)
{
	return 0;
}
	
void SearchAgent::searchPosition(Board& pos, SearchInfo& info)
{

}