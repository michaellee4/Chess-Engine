#ifndef BOARD_H
#define BOARD_H

#include "defs.h"
#include "move.h"
#include "pvtable.h"
#include <string>
#include <vector>
#include <sstream>
/*** The central unit of the Engine ***/
// Handles the entire board representation and all information regarding the board.
class MoveList;
class Board
{
	private:

		/**
		 * Resets all board variables to default values
		 * Called by parseFEN() and flipBoard()
		 */
		void resetBoard(void) noexcept;

		/**
		 * Updates all internal Board vectors related to pieces
		 * Called by parseFEN() and flipBoard()
		 */
		void updatePieceLists(void) noexcept;

		/**
		 * Parses the first FEN argument and places the pieces on the board as indicated
		 * Called by parseFEN()
		 */
		void setUpPieces(const std::string& pieces) noexcept;

		/**
		 * Parses the castle argument of the FEN
		 * Called by parseFEN()
		 */
		void setUpCastlePerm(const std::string& perm) noexcept;

		/**
		 * Parses the enPassant argument of the FEN
		 * Called by parseFEN()
		 */
		void getEnPassant(const std::string& enPas) noexcept;

		/**
		 * Parses the ply counter argument(s) of the FEN if they exist
		 * Called by parseFEN()
		 */
		void setUpMoveCounters(std::istringstream& stream, std::string& section) noexcept;

	public:
		// stores the state of the board 120 sq representation
		std::vector<uint32_t> pieces; 

		// stores a pawn bitboard for white/black/both pawns
		std::vector<uint64_t> pawns;

		// stores king positions
		std::vector<int32_t> king_sq;

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

		// stores castle permissions using 4 bits
		uint32_t castle_perm;
		
		// keeps track of how many of each pice is present on the board and where they are
		std::vector<std::vector<uint32_t>> piece_list;

		// non pawn pieces
		std::vector<uint32_t> big_pce;

		// rooks and queens
		std::vector<uint32_t> maj_pce;

		// bishops and knights
		std::vector<uint32_t> min_pce;

		std::vector<uint32_t> material;

		// stores the history of moves
		std::vector<UndoMove> history;

		std::vector<std::vector<int32_t>> search_hist;

		std::vector<std::vector<Move>> search_killers;
	public:
		Board() noexcept;

		Board(const std::string& fen) noexcept;

		/**
		 * Input: A Forsyth-Edwards Notation string
		 * Output: None, will internally set up the 
		 *		   Board representation of the calling
		 *		   Board object.
		 *
		 * Example: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
		 *							^							^	^  ^ ^ ^
		 *							1							2	3  4 5 6
		 *
		 * 1. Piece locations
		 * 2. Current side to move
		 * 3. Castling permissions
		 * 4. EnPassant square
		 * 5. Halfmove clock (fifty move count)
		 * 6. Fullmove number
		 */
		void parseFEN(const std::string&) noexcept;

		/**
		 * Input: Target square in array-120 format
		 *		 Attacking side (WHITE, BLACK)
		 * Output: Number of times target sq is attacked by provided side
		 */		
		uint32_t sqAttacked(const uint32_t sq, const uint32_t side) const noexcept;

		/**
		 * Output: A MoveList object with all possible moves (including moves where king is in check)
		 */
		MoveList getAllMoves() const noexcept;

		/**
		 * Output: A MoveList object with all possible capture moves (including moves where king is in check)
		 * Used in Queiescence search
		 */
		MoveList getAllCaptureMoves() const noexcept;
		
		/**
		 * Flips the internal Board representation along the central file
		 * Used primarily for debugging search evaluation
		 * Assert(eval(pos) == eval(pos.flipBoard()))
		 */
		void flipBoard() noexcept;

		/**
		 * Output: true if the current side to move is in check, false otherwise.
		 */
		bool inCheck() noexcept;
};

#endif
