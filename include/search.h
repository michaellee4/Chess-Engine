#ifndef SEARCH_H
#define SEARCH_H
#include "defs.h"
#include "board.h"
#include "searchinfo.h"
#include "eval.h"
// Piece Value tables for positional evaluation

class SearchAgent
{
private:
	static constexpr uint32_t kInterval = 0x7FF;
	int32_t isRepetition(const Board& pos) noexcept;
	void checkStop(SearchInfo& info);
	void clearForSearch(Board& pos, SearchInfo& info) noexcept;
	int32_t alphaBeta(int32_t alpha, int32_t beta, uint32_t depth, Board& pos, SearchInfo& info, bool doNull) noexcept;
	int32_t quiescenceSearch(int32_t alpha, int32_t beta, Board& pos, SearchInfo& info) noexcept;
	bool threeFoldRepetition(const Board& pos) noexcept;
	bool drawnMaterial(const Board& pos) noexcept;
	bool inCheck(const Board& pos) noexcept;

public:
	Evaluator eval;

	void searchPosition(Board& pos, SearchInfo& info) noexcept;
	bool isGameOver(Board& pos) noexcept;
	SearchAgent() noexcept;
};

#endif