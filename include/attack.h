/**
*	@file attack.h
*	@brief Contains constant offsets for each piece that represents each possible move
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef ATTACK_H
#define ATTACK_H

// Lists attack patterns for Pieces on the 120 Sq board.
namespace Attack
{
	constexpr std::array<int32_t, 2> wPCap   { -11, -9 };
	constexpr std::array<int32_t, 2> bPCap   {  11,  9 };
	constexpr std::array<int32_t, 2> PnMoves { -10, 10 };
	constexpr std::array<int32_t, 8> KnMoves { -8, -19, -21, -12, 8, 19, 21, 12 };
	constexpr std::array<int32_t, 4> RkMoves { -1, -10, 1, 10 };
	constexpr std::array<int32_t, 4> BiMoves { -9, -11, 11, 9 };
	constexpr std::array<int32_t, 8> KiMoves { -1, -10, 1, 10, -9, -11, 11, 9 };
}

#endif