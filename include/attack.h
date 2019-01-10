/**
*	@file attack.h
*	@brief Contains constant offsets for each piece that represents each possible move
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef ATTACK_H
#define ATTACK_H

/**
*	@brief Provides offsets in array-120 form for a move in each possible direction for each piece
*/
namespace Attack
{
/**
*	@brief Provides the diagonal capture moves for white Pawns
*/
	constexpr std::array<int32_t, 2> wPCap   { -11, -9 };
/**
*	@brief Provides the diagonal capture moves for black Pawns
*/
	constexpr std::array<int32_t, 2> bPCap   {  11,  9 };
/**
*	@brief Provides the possible moves for a white or black Pawn
*/
	constexpr std::array<int32_t, 2> PnMoves { -10, 10 };
/**
*	@brief Provides the possible moves for a white or black King
*/
	constexpr std::array<int32_t, 8> KnMoves { -8, -19, -21, -12, 8, 19, 21, 12 };
/**
*	@brief Provides the possible moves for a white or black Rook
*/
	constexpr std::array<int32_t, 4> RkMoves { -1, -10, 1, 10 };
/**
*	@brief Provides the possible moves for a white or black Bishop
*/
	constexpr std::array<int32_t, 4> BiMoves { -9, -11, 11, 9 };
/**
*	@brief Provides the possible moves for a white or black King
*/
	constexpr std::array<int32_t, 8> KiMoves { -1, -10, 1, 10, -9, -11, 11, 9 };
}

#endif