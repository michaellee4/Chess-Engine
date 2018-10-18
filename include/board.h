#ifndef BOARD_H
#define BOARD_H

#include "defs.h"
#include "move.h"

class Board
{
	public:
		// stores the state of the board
		int pieces[BRD_SQ_NUM];

		// stores a pawn bitboard for white/black/both pawns
		U64 pawns[3];

		// stores king positions
		int kingSq[2];

		// tracks which player is up to move
		int side_to_move;

		// trackes the enPassant square, if there is one
		int enPas;

		// tracks the number of turns made (not ply)
		int fiftyMove;

		// number of half moves
		int ply;

		// total number of plys
		int histPly;

		// position hash
		U64 posKey;

		// keeps track of how many of each pice is present on the board
		int piece_num[13];

		// non pawn pieces
		int bigPce[3];

		// rooks and queens
		int majPce[3];

		// bishops and knights
		int minPce[3];

		// stores castle permissions using 4 bits
		int castlePerm;

		// stores the history of moves
		Move history[MAX_GAME_MOVES];

		// piece list
		int pList[13][10];
};

#endif