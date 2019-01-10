/**
*	@file polyglot.cc
*	@brief Contains definitions of functions declared in polyglot.h.
*	@author Michael Lee
*	@date 1/9/2019
*/
#include "defs.h"
#include "polyglotkeys.h"
#include "polyglot.h"
#include "board.h"
#include "io.h"
#include "move.h"
#include "utils.h"
#include <sstream>
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

bool PolyBook::readBook()
{
	std::ifstream polyBook("lib/polyglot-collection/Performance.bin", std::ios::binary | std::ios::ate);

	if(!polyBook.is_open())
	{
		std::cout << "Unable to open polyglot book" << std::endl;
	}
	else
	{
		uint64_t fileSize = polyBook.tellg();
		polyBook.clear();
		polyBook.seekg(0, std::ios::beg);
		uint64_t numEntries = fileSize / sizeof(PolyglotEntry);

		this->book = std::vector<PolyglotEntry>(numEntries);
		if(polyBook.read((char*)this->book.data(), fileSize))
		{
			// successfully read file into vector
			return true;
		}
		else
		{
			std::cout << "Unable to read polyglot book into buffer" << std::endl;	
		}
	}
	return true;
}

uint16_t PolyBook::endian_swap_u16(uint16_t x)
{
	x = (x >> 8) | (x << 8);
	return x;
}

uint32_t PolyBook::endian_swap_u32(uint32_t x)
{
    x = (x>>24) | 
        ((x<<8) & 0x00FF0000) | 
        ((x>>8) & 0x0000FF00) | 
        (x<<24); 
    return x;
}

uint64_t PolyBook::endian_swap_u64(uint64_t x)
{								 
    x = (x>>56) | 
        ((x<<40) & 0x00FF000000000000) | 
        ((x<<24) & 0x0000FF0000000000) | 
        ((x<<8)  & 0x000000FF00000000) | 
        ((x>>8)  & 0x00000000FF000000) | 
        ((x>>24) & 0x0000000000FF0000) | 
        ((x>>40) & 0x000000000000FF00) | 
        (x<<56); 
    return x;
}

Move PolyBook::convertPolyMove(uint16_t polyMove, const Board& pos)
{
	std::stringstream ss;
	ss << IO::FileChar[(polyMove >> 6) & 0x7]
	   << IO::RankChar[(polyMove >> 9) & 0x7]
	   << IO::FileChar[(polyMove >> 0) & 0x7]
	   << IO::RankChar[(polyMove >> 3) & 0x7];
	uint8_t prom = (polyMove >> 12) & 0x7;
	if( prom != 0)
	{
		char promChar = 'q';
		switch(prom)
		{
			case 1: promChar = 'n'; 
			break;
			case 2: promChar = 'b';
			break;
			case 3: promChar = 'r';
			break;
		}
		ss << promChar;
	}
	return IO::parseMove(ss.str(), pos);
}

Move PolyBook::getBookMove(Board& pos)
{
	uint64_t polyKey = polyKeyFromBoard(pos);

	std::vector<Move> bookMoves;
	for(auto pe : this->book)
	{
		if(endian_swap_u64(pe.key) == polyKey)
		{
			uint16_t move = endian_swap_u16(pe.move);
			Move tmpMove = convertPolyMove(move, pos);
			if(!tmpMove.isNull())
			{
				bookMoves.push_back(tmpMove);	
			}
		}
	}

	if(!bookMoves.empty())
	{
		int32_t idx = randU64() % bookMoves.size();
		return bookMoves[idx];
	}
	return NOMOVE;
}
