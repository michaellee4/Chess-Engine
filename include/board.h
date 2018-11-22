#ifndef BOARD_H
#define BOARD_H

#include "defs.h"
#include "move.h"
#include <string>
#include <vector>
// change all arrays to vector
class Board
{
	public:
		// stores the state of the board 120 sq representation
		int pieces[BRD_SQ_NUM]; 

		// stores a pawn bitboard for white/black/both pawns
		std::vector<U64> pawns;

		// stores king positions
		std::vector<int> king_sq;

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
		std::vector<int> piece_num;

		// piece list
		int piece_list[13][10];

		// non pawn pieces
		std::vector<int> big_pce;

		// rooks and queens
		std::vector<int> maj_pce;

		// bishops and knights
		std::vector<int> min_pce;

		std::vector<int> material;

		// stores castle permissions using 4 bits
		int castle_perm;

		// stores the history of moves
		std::vector<U_Move> history;

		Board();

		Board(const std::string fen);

		void ResetBoard(void);

		void ParseFEN(const std::string);

		void PrintBoard(void) const;

		void UpdatePieceLists(void);

		bool SqOnBoard(int sq) const;

		void PrintMoveList(void) const;

		void GenerateAllMoves(void);
		
		int SqAttacked(const int sq, const int side) const;

};
		bool CheckBoard(const Board& pos);
#endif