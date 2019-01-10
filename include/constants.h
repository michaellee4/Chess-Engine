/**
*	@file constants.h
*	@brief Contains declarations of various constant arrays used throughout the engine
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef DEFS_H
#define DEFS_H

#include "debug.h"
#include "move.h"
#include <string>
#include <array>
#include<cstddef>
#define STARTFEN  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

/**
*	@brief The search limit, only ever used when no depth limit is given by the gui or infinite search is on.
*/
constexpr uint32_t kMaxSearchDepth = 64;

/**
*	@brief The maximum possible moves allowed for an game of chess.
*/
constexpr uint32_t kMoveLimit = 2 << 10;

/**
*	@brief The size if the internal board representation.
*/
constexpr uint32_t kBoardArraySize = 120;

/**
*	@brief The actual size of a chessboard.
*/
constexpr uint32_t kChessboardSize = 64;

/**
*	@brief The number of players in a game of chess.
*/
constexpr uint32_t kNumPlayers = 2;

/**
*	@brief The length/width of a chessboard.
*/
constexpr uint32_t kNumFilesRanks = 8;

/**
*	@brief The total number of different pieces.
*/
constexpr uint32_t kNumPceTypes = 13;

/**
*	@brief The default name of the chess engine.
*/
const std::string kAppName = "ChessEngine";

/**
*	@brief The integer values for each piece
*/
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
/**
*	@brief The integer values for each file
*/
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
/**
*	@brief The integer values for each rank
*/
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };
/**
*	@brief The integer values for the sides
*/
enum { WHITE, BLACK, BOTH };
/**
*	@brief The integer values for each square that is on the board, NO_SQ is used for the EnPas square
*/
enum {
	A1 = 21, B1, C1, D1, E1, F1, G1, H1,
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3,
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

/**
*	@brief The bit layout for each individual castle perm combined using bitwise |
*/
enum { WKCA = 0b0001, WQCA = 0b0010, BKCA = 0b0100, BQCA = 0b1000 };

/**
*	@brief Flags used in the transposition table
*/
enum {  HFNONE, HFALPHA, HFBETA, HFEXACT};

/**
*	@brief Represents an illegal or invalid move
*/
const Move NOMOVE(0);

#endif
