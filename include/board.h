#ifndef BOARD_H
#define BOARD_H

#include "defs.h"
#include "move.h"
#include <string>

// change all arrays to vector
class Board
{
	public:
		// stores the state of the board 120 sq representation
		int pieces[BRD_SQ_NUM]; 

		// stores a pawn bitboard for white/black/both pawns
		U64 pawns[3];

		// stores king positions
		int king_sq[2];

		// tracks which player is up to move
		int side_to_move;

		// trackes the enPassant square, if there is one
		int en_pas;

		// tracks the number of turns made (not ply)
		int fifty_move;

		// number of half moves
		int ply;

		// total number of plys
		int hist_ply;

		// position hash
		U64 pos_key;

		/*** Replace pieceList and PieceNum with 1 2d vector or LL ***/
		// keeps track of how many of each pice is present on the board
		int piece_num[13];

		// piece list
		int piece_list[13][10];

		// non pawn pieces
		int big_pce[2];

		// rooks and queens
		int maj_pce[2];

		// bishops and knights
		int min_pce[2];

		int material[2];

		// stores castle permissions using 4 bits
		int castle_perm;

		// stores the history of moves
		U_Move history[MAX_GAME_MOVES];

		void ResetBoard(void);

		void ParseFEN(std::string);

		void PrintBoard(void) const;

		void UpdatePieceLists(void);

		bool SqOnBoard(int sq) const;

		void PrintMoveList(void) const;

		void GenerateAllMoves(void);
		
		int SqAttacked(const int sq, const int side) const;

};
		bool CheckBoard(const Board& pos);
#endif