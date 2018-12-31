#include "defs.h"
#include "polyglotkeys.h"
#include "polyglot.h"
#include "board.h"
#include "utils.h"

bool Polyglot::enPasPossible(const Board& pos)
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

uint64_t Polyglot::polyKeyFromBoard(const Board& pos)
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