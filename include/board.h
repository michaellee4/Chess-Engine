#ifndef BOARD_H
#define BOARD_H

#include "defs.h"
#include "move.h"
#include <string>
#include <vector>
#include "pvtable.h"
/*** The central unit of the Engine ***/
// Handles the entire board representation and all information regarding the board.
class Board
{
	private:
		// Resets the board to the empty state
		void ResetBoard(void);

		// Update the underlying board information arrays
		void UpdatePieceLists(void);

		// Places the pieces on the board using the fen
		void SetUpPieces(const std::string& section);

		// Sets up castling permissions with the fen
		void GetCastlePerm(const std::string& section);

		void GetEnPassant(const std::string& section);

		void GetMoveCounters(std::istringstream& stream, std::string& section);

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

		// number of half moves in the current search
		int32_t ply;

		// total number of half moves in the entire game
		int32_t hist_ply;

		// position hash
		uint64_t pos_key;

		// keeps track of how many of each pice is present on the board and where they are
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

		// Principal variation table
		PV_Table pv_table;
		
		std::vector<Move> pv_arr;

		std::vector<std::vector<uint32_t>> search_hist;

		std::vector<std::vector<uint32_t>> search_killers;

		Board();

		Board(const std::string fen);

		// Reads in a Forseth-Edwards Notation string and prepares the board in accordance ot it.
		void ParseFEN(const std::string);

		// Prints out the current state of the board
		// void PrintBoard(void) const;

		// Checks if a sq is on the board
		bool SqOnBoard(uint32_t sq) const;
		
		// returns the number of times that a Sq is attacked by the given side
		uint32_t SqAttacked(const uint32_t sq, const uint32_t side) const;

};
		// reconstructs the board state and checks if they match
		// Used for debugging.
		bool CheckBoard(const Board& pos);
#endif
