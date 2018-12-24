#ifndef DEFS_H
#define DEFS_H

#include "debug.h"
#include<vector>
#include<unordered_map>
#include<cstddef>
#include "move.h"
#include "pvtable.h"
#define STARTFEN  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

const uint32_t MAX_DEPTH = 64;

const uint32_t PCE_TYPES = 13;

const uint32_t BRD_ARR_SIZE = 120;

const uint32_t CHESSBOARD_SIZE = 64;

const uint32_t MAX_GAME_MOVES = 2 << 10;

const uint32_t NUM_SIDES = 2;

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

// Provides dictionaries for used in toString() functions
namespace BoardChar
{
	const std::string PceChar = ".PNBRQKpnbrqk";
	const std::string SideChar = "wb-";
	const std::string RankChar = "12345678";
	const std::string FileChar = "abcdefgh";
	const std::unordered_map<uint32_t, std::string> epstr = 
	{{71,"a6"}, {72,"b6"}, {73,"c6"}, {74,"d6"}, {75,"e6"}, {76,"f6"}, {77,"g6"}, {78,"h6"},
	 {41,"a3"}, {42,"b3"}, {43,"c3"}, {44,"d3"}, {45,"e3"}, {46,"f3"}, {47,"g3"}, {48,"h3"}, {99, "None"}};
}

// Provides dictionaries to get information about a piece
namespace PieceInfo
{
	const std::vector<bool> PieceBig { false, false, true, true, true, true, true, false, true, true, true, true, true };
	const std::vector<bool> PieceMaj { false, false, false, false, true, true, true, false, false, false, true, true, true };
	const std::vector<bool> PieceMin { false, false, true, true, false, false, false, false, true, true, false, false, false };
	const std::vector<uint32_t> PieceVal  { 0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000  };
	const std::vector<uint32_t> PieceCol  { BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
											BLACK, BLACK, BLACK, BLACK, BLACK, BLACK };
	const std::vector<bool> PieceSlides = { false, false, false, true, true, true, false, false, false, true, true, true, false };

	const std::vector<bool> PiecePawn = { false, true, false, false, false, false, false, true, false, false, false, false, false };	
	const std::vector<bool> PieceKing = { false, false, false, false, false, false, true, false, false, false, false, false, true };
	const std::vector<bool> PieceRookQueen = { false, false, false, false, true, true, false, false, false, false, true, true, false };
	const std::vector<bool> PieceBishopQueen = { false, false, false, true, false, true, false, false, false, true, false, true, false };
	const std::vector<bool> PieceKnight = { false, false, true, false, false, false, false, false, true, false, false, false, false };

 }

// Lists attack patterns for Pieces on the 120 Sq board.
namespace Attack
{
	const std::vector<int> wPCap   { -11, -9 };
	const std::vector<int> bPCap   {  11,  9 };
	const std::vector<int> PnMoves { -10, 10 };
	const std::vector<int> KnMoves { -8, -19, -21, -12, 8, 19, 21, 12 };
	const std::vector<int> RkMoves { -1, -10, 1, 10 };
	const std::vector<int> BiMoves { -9, -11, 11, 9 };
	const std::vector<int> KiMoves { -1, -10, 1, 10, -9, -11, 11, 9 };
}

namespace BoardUtils
{
	// *** initialized in init
	extern std::vector<int32_t> Sq120ToSq64;
	extern std::vector<int32_t> Sq64ToSq120;
	extern std::vector<int32_t> FileBrd;
	extern std::vector<int32_t> RankBrd;
}

const Move NOMOVE(0);
#endif
