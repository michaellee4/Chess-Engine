#ifndef POLYGLOT_H
#define POLYGLOT_H
#include "defs.h"
#include <vector>

struct PolyglotEntry
{
	uint64_t key;
	uint16_t move;
	uint16_t weight;
	uint32_t learn;
};

class PolyBook
{
private:
	static constexpr std::array<int32_t, 13> polyPiece { -1, 1, 3, 5, 7, 9, 11, 0, 2, 4, 6, 8, 10};
	static bool enPasPossible(const Board& pos);
	std::vector<PolyglotEntry> book;
public:
	static uint64_t polyKeyFromBoard(const Board& pos);
	void clear() noexcept;
	void readBook();
	PolyBook() noexcept;
	// ~PolyBook() noexcept;
};

#endif