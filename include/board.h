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
		std::vector<uint32_t> pieces; 

		// stores a pawn bitboard for white/black/both pawns
		std::vector<uint64_t> pawns;

		// stores king positions
		std::vector<int> king_sq;

		// tracks which player is up to move
		uint32_t side_to_move;

		// trackes the enPassant square, if there is one
		uint32_t en_pas;

		// tracks the number of turns made (not ply)
		uint32_t fifty_move;

		// number of half moves
		int ply;

		// total number of plys
		int hist_ply;

		// position hash
		uint64_t pos_key;

		// keeps track of how many of each pice is present on the board and where they are
		// piece list
		std::vector<std::vector<uint32_t>> piece_list;

		// non pawn pieces
		std::vector<uint32_t> big_pce;

		// rooks and queens
		std::vector<uint32_t> maj_pce;

		// bishops and knights
		std::vector<uint32_t> min_pce;

		std::vector<uint32_t> material;

		// stores castle permissions using 4 bits
		uint32_t castle_perm;

		// stores the history of moves
		std::vector<U_Move> history;

		Board();

		Board(const std::string fen);

		void ResetBoard(void);

		void ParseFEN(const std::string);

		void PrintBoard(void) const;

		void UpdatePieceLists(void);

		bool SqOnBoard(uint32_t sq) const;
		
		uint32_t SqAttacked(const uint32_t sq, const uint32_t side) const;

};
		bool CheckBoard(const Board& pos);
#endif