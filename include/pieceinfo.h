/**
*	@file pieceinfo.h
*	@brief Contains constant that provide information indexed by pieces
*	@author Michael Lee
*	@date 1/9/2019
*/

#ifndef PIECEINFO_H
#define PIECEINFO_H

namespace PieceInfo
{
	constexpr std::array<bool, kNumPceTypes> PieceBig { false, false, true, true, true, true, true, false, true, true, true, true, true };
	constexpr std::array<bool, kNumPceTypes> PieceMaj { false, false, false, false, true, true, true, false, false, false, true, true, true };
	constexpr std::array<bool, kNumPceTypes> PieceMin { false, false, true, true, false, false, false, false, true, true, false, false, false };
	constexpr std::array<uint32_t, kNumPceTypes> PieceVal  { 0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000  };
	constexpr std::array<uint32_t, kNumPceTypes> PieceCol  { BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK };
	constexpr std::array<bool, kNumPceTypes> PieceSlides { false, false, false, true, true, true, false, false, false, true, true, true, false };
	constexpr std::array<bool, kNumPceTypes> PiecePawn { false, true, false, false, false, false, false, true, false, false, false, false, false };	
	constexpr std::array<bool, kNumPceTypes> PieceKing { false, false, false, false, false, false, true, false, false, false, false, false, true };
	constexpr std::array<bool, kNumPceTypes> PieceRookQueen { false, false, false, false, true, true, false, false, false, false, true, true, false };
	constexpr std::array<bool, kNumPceTypes> PieceBishopQueen { false, false, false, true, false, true, false, false, false, true, false, true, false };
	constexpr std::array<bool, kNumPceTypes> PieceKnight { false, false, true, false, false, false, false, false, true, false, false, false, false };
 }


#endif