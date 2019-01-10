/**
*	@file board.h
*	@brief Defines the internal Board representation used by the engine.
*	@author Michael Lee
*	@date 1/9/2019
*/

#ifndef BOARD_H
#define BOARD_H

#include "defs.h"
#include "move.h"
#include "pvtable.h"
#include <string>
#include <vector>
#include <sstream>
class MoveList;

/** 
* Handles the entire board representation and all information regarding the board.
*/
class Board
{
private:
/**
	@brief Resets all board variables to default values.
	@param None
	@return None
 */
	void resetBoard(void) noexcept;

/**
	@brief Updates all internal Board vectors related to pieces.
	@param None
	@return None
 */
	void updatePieceLists(void) noexcept;
/**
	@brief Parses the first FEN argument and places the pieces on the board as indicated.
	@param None
	@return None
 */
	void setUpPieces(const std::string& pieces) noexcept;

/**
	@brief Parses the castle argument of the FEN.
	@param None
	@return None
 */
	void setUpCastlePerm(const std::string& perm) noexcept;

/**
	@brief Parses the enPassant argument of the FEN.
	@param None
	@return None
 */
	void getEnPassant(const std::string& enPas) noexcept;

/**
	@brief Parses the ply counter argument(s) of the FEN if they exist.
	@param None
	@return None
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
	 * @brief Set up the Board representation of the calling Board object.
	 <pre>
Example: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
                          ^							 ^	^   ^ ^ ^
                          1							 2	3   4 5 6
	 </pre>
	 * 1. Piece locations
	 * 2. Current side to move
	 * 3. Castling permissions
	 * 4. EnPassant square
	 * 5. Halfmove clock (fifty move count)
	 * 6. Fullmove number
	 * @param fen The Forsyth-Edwards Notation string
	 * @return None
	 */
	void parseFEN(const std::string&) noexcept;
/**
	@brief Gets the number of times a square is attacked by a given side.
	@param sq The target square.
	@param side The attacking side
	@return The number of times the target square is attacked by the given side
 */
	uint32_t sqAttacked(const uint32_t sq, const uint32_t side) const noexcept;
/**
	@brief Gets all the possible moves, including ones that happen during check.
	@param None
	@return A MoveList with all possible moves
 */
	MoveList getAllMoves() const noexcept;
/**
	@brief Get all possible moves that involve capture, including ones that happen during check.
	@param None
	@return A MoveList with all possible capture moves.
 */
	MoveList getAllCaptureMoves() const noexcept;
/**
	@brief Flips the internal Board representation along the central file.
	@param None
	@return None
 */
	void flipBoard() noexcept;
/**
	@brief Checks if the current side is in check.
	@param None
	@return true if the current side to move is in check, false otherwise.
 */
	bool inCheck() noexcept;
};

#endif
