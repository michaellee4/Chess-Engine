#ifndef DEFS_H
#define DEFS_H

#include "debug.h"
#include<vector>
#include<unordered_map>
#include<cstddef>
#include "move.h"
#include "pvtable.h"
#include <string>
#include <array>
#define STARTFEN  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

constexpr uint32_t kMaxSearchDepth = 64;

constexpr uint32_t kNumPceTypes = 13;

constexpr uint32_t kBoardArraySize = 120;

constexpr uint32_t kChessboardSize = 64;

constexpr uint32_t kMoveLimit = 2 << 10;

constexpr uint32_t kNumPlayers = 2;

constexpr uint32_t kNumFilesRanks = 8;

const std::string kAppName = "ChessEngine";
// pieces
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };

// columns
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };

// rows
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };

// sides
enum { WHITE, BLACK, BOTH };

// int value of actual board squares
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

// Castling permissions
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 };

// Current mode
enum { UCI_MODE, XBOARD_MODE, CONSOLE_MODE};
// Provides dictionaries to get information about a piece
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

namespace BoardUtils
{
	// *** initialized in init
	extern std::array<int32_t, kBoardArraySize> Sq120ToSq64;
	extern std::array<int32_t, kChessboardSize> Sq64ToSq120;
	extern std::array<int32_t, kBoardArraySize> FileBrd;
	extern std::array<int32_t, kBoardArraySize> RankBrd;
}

const Move NOMOVE(0);
#endif
