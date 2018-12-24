#include "defs.h"
#include "utils.h"
#include "init.h"
#include "hash.h"
#include "bitboard.h"
#include <vector>
// std::vector<int32_t> BoardUtils::Sq120ToSq64(BRD_SQ_NUM);
// std::vector<int32_t> BoardUtils::Sq64ToSq120(64);

// int BoardUtils::FileBrd[BRD_SQ_NUM];
// int BoardUtils::RankBrd[BRD_SQ_NUM];

namespace BoardUtils
{
	// *** used in init
	std::vector<int32_t> Sq120ToSq64(BRD_SQ_NUM);
	std::vector<int32_t> Sq64ToSq120(64);
	//*** used in utils
	std::vector<int32_t> FileBrd(BRD_SQ_NUM);
	std::vector<int32_t> RankBrd(BRD_SQ_NUM);
}

namespace Hash
{
	std::vector<std::vector<uint64_t>> PieceKeys(13, std::vector<uint64_t>(120));
	uint64_t SideKey;
	std::vector<uint64_t> CastleKeys(16);
}

uint64_t SetMask[64];
uint64_t ClearMask[64];

void initFileRankBrd()
{
	for(uint32_t sq = 0; sq < BRD_SQ_NUM; ++sq)
	{
		BoardUtils::FileBrd[sq] = OFFBOARD;
		BoardUtils::RankBrd[sq] = OFFBOARD;
	}

	for(uint32_t rank = RANK_1; rank<=RANK_8; ++rank)
	{
		for(uint32_t file = FILE_A; file <= FILE_H; ++file)
		{
			int sq = fileRankToSq(file, rank);
			BoardUtils::FileBrd[sq] = file;
			BoardUtils::RankBrd[sq] = rank;
		}
	}
}

// creates 2 arrays to map 64 <-> 120 board square representations
void initSq120ToSq64()
{
	int sq64 = 0;

	for(uint32_t index = 0; index < BRD_SQ_NUM; ++index)
	{
		// use 65 as invalid value
		BoardUtils::Sq120ToSq64[index] = 65;
	}

	for(uint32_t index = 0; index < 64; ++index)
	{
		BoardUtils::Sq64ToSq120[index] = 65;
	}

	for(uint32_t rank = RANK_1; rank <= RANK_8; ++rank)
	{
		for(uint32_t file = FILE_A; file <= FILE_H; ++file)
		{
			int sq = fileRankToSq(file, rank);
			BoardUtils::Sq64ToSq120[sq64] = sq;
			BoardUtils::Sq120ToSq64[sq] = sq64;
			++sq64;
		}
	}
}

void initBitMasks()
{
	for(uint32_t index = 0; index < 64; ++index)
	{
		SetMask[index] = 1ULL << index;
		ClearMask[index] = ~SetMask[index];
	}
}

void initHashKeys()
{
	for(uint32_t i = 0; i < 13; ++i )
	{
		for(uint32_t j = 0; j < 120; ++j)
		{
			Hash::PieceKeys[i][j] = randU64();
		}
	}
	Hash::SideKey = randU64();

	for(uint32_t i = 0; i < 16; ++i )
	{
		Hash::CastleKeys[i] = randU64();
	}
}

void initAll()
{
	initSq120ToSq64();
	initBitMasks();
	initHashKeys();
	initFileRankBrd();
}