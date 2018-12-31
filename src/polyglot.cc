#include "defs.h"
#include "polyglotkeys.h"
#include "polyglot.h"
#include "board.h"
#include "utils.h"
#include <fstream>
#include <iostream>

PolyBook::PolyBook() noexcept : book() {}
bool PolyBook::enPasPossible(const Board& pos)
{
	uint32_t tgtSq = 0;
	uint32_t tgtPce = pos.side_to_move == WHITE ? wP : bP;
	if(pos.en_pas != NO_SQ)
	{
		if(pos.side_to_move == WHITE)
		{
			tgtSq = pos.en_pas - 10;
		}
		else
		{
			tgtSq = pos.en_pas + 10;
		}
		if(pos.pieces[tgtSq + 1] == tgtPce || pos.pieces[tgtSq - 1] == tgtPce)
		{
			return true;
		}
	}
	return false;
}

uint64_t PolyBook::polyKeyFromBoard(const Board& pos)
{
	uint64_t posPolyKey = 0;

	for(uint32_t sq = 0; sq < kBoardArraySize; ++sq)
	{
		int32_t pce = pos.pieces[sq];
		if(pce != NO_SQ && pce != EMPTY && pce != OFFBOARD)
		{
			int32_t polyPce = polyPiece[pce];
			int32_t rank = BoardUtils::RankBrd[sq];
			int32_t file = BoardUtils::FileBrd[sq];
			int32_t pceOffset = kChessboardSize * polyPce + (kNumFilesRanks * rank) + file;
			posPolyKey ^= PolyKeys::Random64[pceOffset];
		}
	}
	constexpr int32_t castleOffset = (kNumPceTypes - 1) * kChessboardSize;

	if(pos.castle_perm & WKCA) posPolyKey ^= PolyKeys::Random64[castleOffset + 0];
	if(pos.castle_perm & WQCA) posPolyKey ^= PolyKeys::Random64[castleOffset + 1];
	if(pos.castle_perm & BKCA) posPolyKey ^= PolyKeys::Random64[castleOffset + 2];
	if(pos.castle_perm & BQCA) posPolyKey ^= PolyKeys::Random64[castleOffset + 3];

	constexpr int32_t enPasOffset = castleOffset + 4;
	if(enPasPossible(pos))
	{
		int32_t file = BoardUtils::FileBrd[pos.en_pas];
		posPolyKey ^= PolyKeys::Random64[enPasOffset + file];
	}

	constexpr int32_t sideOffset = 780;
	if(pos.side_to_move == WHITE)
	{
		posPolyKey ^= PolyKeys::Random64[sideOffset];
	}
	return posPolyKey;
}

void PolyBook::readBook()
{
	// std::ifstream polyBook("lib/polyglot-collection/Performance.bin", std::ios::binary | std::ios::ate);

	// if(!polyBook.is_open())
	// {
	// 	std::cout << "Unable to open polyglot book" << std::endl;
	// }
	// else
	// {
	// 	uint64_t fileSize = polyBook.tellg();
	// 	polyBook.clear();
	// 	polyBook.seekg(0, std::ios::beg);
	// 	int32_t numEntries = fileSize / sizeof(PolyglotEntry);

	// 	this->book = std::vector<PolyglotEntry>(numEntries);
	// 	if(polyBook.read((uint8_t*)this->book.data(), fileSize))
	// 	{

	// 	}
	// 	else
	// 	{
	// 		std::cout << "Unable to read polyglot book into buffer" << std::endl;	
	// 	}
	// }

}
