#include "defs.h"
#include "utils.h"
#include "init.h"
#include "hash.h"
#include "bitboard.h"
#include "movelist.h"
#include <vector>

namespace BoardUtils
{
	// *** used in init
	std::vector<int32_t> Sq120ToSq64(BRD_ARR_SIZE);
	std::vector<int32_t> Sq64ToSq120(CHESSBOARD_SIZE);
	//*** used in utils
	std::vector<int32_t> FileBrd(BRD_ARR_SIZE);
	std::vector<int32_t> RankBrd(BRD_ARR_SIZE);
}

namespace Hash
{
	std::vector<std::vector<uint64_t>> PieceKeys(PCE_TYPES, std::vector<uint64_t>(BRD_ARR_SIZE));
	uint64_t SideKey;
	std::vector<uint64_t> CastleKeys(16);
}
namespace BB
{
	std::vector<uint64_t> SetMask(CHESSBOARD_SIZE);
	std::vector<uint64_t> ClearMask(CHESSBOARD_SIZE);
}

namespace MvvLva
{
	std::vector<std::vector<int32_t>> MvvLvaScore(PCE_TYPES, std::vector<int32_t>(PCE_TYPES));
}

void Init::initFileRankBrd() noexcept
{
	for(uint32_t sq = 0; sq < BRD_ARR_SIZE; ++sq)
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
void Init::initSq120ToSq64() noexcept
{
	int sq64 = 0;

	for(uint32_t index = 0; index < BRD_ARR_SIZE; ++index)
	{
		// use 65 as invalid value
		BoardUtils::Sq120ToSq64[index] = 65;
	}

	for(uint32_t index = 0; index < CHESSBOARD_SIZE; ++index)
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

void Init::initBitMasks() noexcept
{
	for(uint32_t index = 0; index < CHESSBOARD_SIZE; ++index)
	{
		BB::SetMask[index] = 1ULL << index;
		BB::ClearMask[index] = ~BB::SetMask[index];
	}
}

void Init::initHashKeys() noexcept
{
	for(uint32_t i = 0; i < PCE_TYPES; ++i )
	{
		for(uint32_t j = 0; j < BRD_ARR_SIZE; ++j)
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

void Init::initMvvLva() noexcept
{
	for (int32_t atk = wP; atk <= bK; ++atk)
	{
		for(int32_t vic = wP; vic <= bK; ++vic)
		{
			MvvLva::MvvLvaScore[vic][atk] = MvvLva::victimScore[vic] + 6 - (MvvLva::victimScore[atk] / 100);
		}
	}
}

void Init::initAll() noexcept
{
	initSq120ToSq64();
	initBitMasks();
	initHashKeys();
	initFileRankBrd();
	initMvvLva();
}