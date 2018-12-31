#include "defs.h"
#include "utils.h"
#include "init.h"
#include "hash.h"
#include "bitboard.h"
#include "io.h"
#include "stopwatch.h"
#include "movelist.h"
#include <vector>
#include <iostream>
namespace BoardUtils
{
	// *** used in init
	std::array<int32_t, kBoardArraySize> Sq120ToSq64;
	std::array<int32_t, kChessboardSize> Sq64ToSq120;
	std::array<int32_t, kBoardArraySize> FileBrd;
	std::array<int32_t, kBoardArraySize> RankBrd;
}
namespace Hash
{
 	std::array<std::array<uint64_t, kBoardArraySize>, kNumPceTypes> PieceKeys;
 	uint64_t SideKey;
	std::array<uint64_t, 16> CastleKeys;
}
namespace BB
{
	std::array<uint64_t, kChessboardSize> SetMask;
	std::array<uint64_t, kChessboardSize> ClearMask;
}
namespace MvvLva
{
	std::array<std::array<int32_t, kNumPceTypes>, kNumPceTypes> MvvLvaScore;
}
namespace EvalBB
{
	std::array<uint64_t, kNumFilesRanks> FileMask;
	std::array<uint64_t, kNumFilesRanks> RankMask;
	std::array<uint64_t, kChessboardSize> whitePassedMask;
	std::array<uint64_t, kChessboardSize> blackPassedMask;
	std::array<uint64_t, kChessboardSize> isolatedMask;
}
void Init::initFileRankBrd() noexcept
{
	for(uint32_t sq = 0; sq < kBoardArraySize; ++sq)
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
	for(uint32_t index = 0; index < kBoardArraySize; ++index)
	{
		// use 65 as invalid value
		BoardUtils::Sq120ToSq64[index] = 65;
	}
	for(uint32_t index = 0; index < kChessboardSize; ++index)
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
	for(uint32_t index = 0; index < kChessboardSize; ++index)
	{
		BB::SetMask[index] = 1ULL << index;
		BB::ClearMask[index] = ~BB::SetMask[index];
	}
}
void Init::initHashKeys() noexcept
{
	for(uint32_t i = 0; i < kNumPceTypes; ++i )
	{
		for(uint32_t j = 0; j < kBoardArraySize; ++j)
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
void Init::initEvalMasks() noexcept
{
	using namespace EvalBB;
	using namespace BoardUtils;
	// initializes the file/rank masks
	for(int32_t r = RANK_8; r >= RANK_1; --r)
	{
		for(int32_t f = FILE_A; f <= FILE_H; ++f)
		{
			int32_t sq = r * kNumFilesRanks + f;
			FileMask[f] |= (1ULL << sq);
			RankMask[r] |= (1ULL << sq);
		}
	}
	for(uint32_t sq = 0; sq < kChessboardSize; ++sq)
	{
		// forward square
		int32_t fsq = sq + kNumFilesRanks;
		while(fsq < (signed)kChessboardSize)
		{
			whitePassedMask[sq] |= (1ULL << fsq);
			fsq += kNumFilesRanks;
		}
		fsq = sq - kNumFilesRanks;
		while(fsq >= 0)
		{
			blackPassedMask[sq] |= (1ULL << fsq);
			fsq -= kNumFilesRanks;
		}
		if(FileBrd[Sq64ToSq120[sq]] > FILE_A)
		{
			isolatedMask[sq] |= FileMask[FileBrd[Sq64ToSq120[sq]] - 1];
			fsq = sq + 7;
			while(fsq < (signed)kChessboardSize)
			{
				whitePassedMask[sq] |= (1ULL << fsq);
				fsq += kNumFilesRanks;
			}
			fsq = sq - 9;
			while(fsq >= 0)
			{
				blackPassedMask[sq] |= (1ULL << fsq);
				fsq -= kNumFilesRanks;
			}
		}
		if(FileBrd[Sq64ToSq120[sq]] < FILE_H)
		{
			isolatedMask[sq] |= FileMask[FileBrd[Sq64ToSq120[sq]] + 1];
			fsq = sq + 9;
			while(fsq < (signed)kChessboardSize)
			{
				whitePassedMask[sq] |= (1ULL << fsq);
				fsq += kNumFilesRanks;
			}
			fsq = sq - 7;
			while(fsq >= 0)
			{
				blackPassedMask[sq] |= (1ULL << fsq);
				fsq -= kNumFilesRanks;
			}
		}
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
	initEvalMasks();
	initMvvLva();
}