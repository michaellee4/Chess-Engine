#ifndef SEARCH_H
#define SEARCH_H
#include "defs.h"
#include "board.h"
#include "searchinfo.h"
class SearchAgent
{
private:
	int32_t isRepetition(const Board& pos);

	void checkStop();

	void clearForSearch(SearchInfo& info);

	int32_t alphaBeta(int32_t alpha, int32_t beta, uint32_t depth, SearchInfo& info, bool doNull);

	int32_t quiescenceSearch(int32_t alpha, int32_t beta, Board& pos, SearchInfo& info);
public:
	void searchPosition(Board& pos, SearchInfo& info);
	static int32_t EvaluatePosition(const Board& pos);
};

#endif