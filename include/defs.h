#ifndef DEFS_H
#define DEFS_H

#include "debug.h"
#include<vector>
#include<unordered_map>

#define START_FEN  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define MAXPOSITIONMOVES 256

typedef unsigned long long U64;

const unsigned int BRD_SQ_NUM = 120;

const unsigned int MAX_GAME_MOVES = 2 << 10;
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

namespace BoardChar
{
	const std::string PceChar = ".PNBRQKpnbrqk";
	const std::string SideChar = "wb-";
	const std::string RankChar = "12345678";
	const std::string FileChar = "abcdefgh";
	const std::unordered_map<int, std::string> epstr = 
	{{71,"a6"}, {72,"b6"}, {73,"c6"}, {74,"d6"}, {75,"e6"}, {76,"f6"}, {77,"g6"}, {78,"h6"},
	 {41,"a3"}, {42,"b3"}, {43,"c3"}, {44,"d3"}, {45,"e3"}, {46,"f3"}, {47,"g3"}, {48,"h3"}, {99, "None"}};
}

 
 namespace PieceInfo
 {
//piece info
	const std::vector<bool> PieceBig { false, false, true, true, true, true, true, false, true, true, true, true, true };
	const std::vector<bool> PieceMaj { false, false, false, false, true, true, true, false, false, false, true, true, true };
	const std::vector<bool> PieceMin { false, false, true, true, false, false, false, false, true, true, false, false, false };
	const std::vector<int> PieceVal  { 0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000  };
	const std::vector<int> PieceCol  { BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
										BLACK, BLACK, BLACK, BLACK, BLACK, BLACK };
	const std::vector<bool> PieceSlides = { false, false, false, true, true, true, false, false, false, true, true, true, false };

	const std::vector<int> PiecePawn = { false, true, false, false, false, false, false, true, false, false, false, false, false };	
	const std::vector<int> PieceKing = { false, false, false, false, false, false, true, false, false, false, false, false, true };
	// const std::vector<int> PieceRookQueen = { false, false, false, false, true, true, false, false, false, false, true, true, false };
	// const std::vector<int> PieceBishopQueen = { false, false, false, true, false, true, false, false, false, true, false, true, false };
	// const std::vector<int> PieceKnight = { false, false, true, false, false, false, false, false, true, false, false, false, false };

 }


namespace Attack
{
	// attackers
	const std::vector<int> KnMoves { -8, -19, -21, -12, 8, 19, 21, 12 };
	const std::vector<int> RkMoves { -1, -10, 1, 10 };
	const std::vector<int> BiMoves { -9, -11, 11, 9 };
	const std::vector<int> KiMoves { -1, -10, 1, 10, -9, -11, 11, 9 };
}


// *** used in init
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];

//*** used in hash
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];

extern int FileBrd[BRD_SQ_NUM];
extern int RankBrd[BRD_SQ_NUM];

#endif
