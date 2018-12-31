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
	bool enPasPossible(const Board& pos);
	uint64_t polyKeyFromBoard(const Board& pos);
	uint16_t endian_swap_u16(uint16_t);
	uint32_t endian_swap_u32(uint32_t);
	uint64_t endian_swap_u64(uint64_t);
	Move convertPolyMove(uint16_t polyMove, const Board& pos);

	std::vector<PolyglotEntry> book;
public:
	void clear() noexcept;
	bool readBook();
	Move getBookMove(Board& pos);
	PolyBook() noexcept;
};

#endif