/**
*	@file pieceinfo.h
*	@brief Contains constant that provide information indexed by pieces
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef PIECEINFO_H
#define PIECEINFO_H

/**
*	@brief Holds Dictionaries to give information for each piece from wP <= piece <= bK
*/
namespace PieceInfo
{
/**
*	@brief Check if a piece is a non-Pawn
*/
	constexpr std::array<bool, kNumPceTypes> PieceBig { false, false, true, true, true, true, true, false, true, true, true, true, true };
/**
*	@brief Check if a piece is a Rook, Queen, or King
*/
	constexpr std::array<bool, kNumPceTypes> PieceMaj { false, false, false, false, true, true, true, false, false, false, true, true, true };
/**
*	@brief Check if a piece is a Bishop or Knight
*/
	constexpr std::array<bool, kNumPceTypes> PieceMin { false, false, true, true, false, false, false, false, true, true, false, false, false };
/**
*	@brief Check the value of a piece in centipawns
*/
	constexpr std::array<uint32_t, kNumPceTypes> PieceVal  { 0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000  };
/**
*	@brief Check the color of a piece
*/
	constexpr std::array<uint32_t, kNumPceTypes> PieceCol  { BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK };
/**
*	@brief Check if a piece is a Bishop, Rook, Queen
*/
	constexpr std::array<bool, kNumPceTypes> PieceSlides { false, false, false, true, true, true, false, false, false, true, true, true, false };
/**
*	@brief Check if a piece is a Pawn
*/
	constexpr std::array<bool, kNumPceTypes> PiecePawn { false, true, false, false, false, false, false, true, false, false, false, false, false };	
/**
*	@brief Check if a piece is a King
*/
	constexpr std::array<bool, kNumPceTypes> PieceKing { false, false, false, false, false, false, true, false, false, false, false, false, true };
/**
*	@brief Check if a piece is a Queen
*/
	constexpr std::array<bool, kNumPceTypes> PieceRookQueen { false, false, false, false, true, true, false, false, false, false, true, true, false };
/**
*	@brief Check if a piece is a Bishop or a Queen
*/
	constexpr std::array<bool, kNumPceTypes> PieceBishopQueen { false, false, false, true, false, true, false, false, false, true, false, true, false };
/**
*	@brief Check if a piece is a Knight
*/
	constexpr std::array<bool, kNumPceTypes> PieceKnight { false, false, true, false, false, false, false, false, true, false, false, false, false };
 }


#endif