/**
*	@file move.h
*	@brief Defines the custom internal move representation.
*	@author Michael Lee
*	@date 1/9/2019
*/

#ifndef MOVE_H
#define MOVE_H

#include <string>
class Board;

/**
	@brief This class stores info needed to undo a move that was made.
*/
class UndoMove
{
	public:
		int32_t move;
		int32_t castle_perm;
		int32_t en_pas;
		int32_t fifty_move;
		uint64_t pos_key;
		UndoMove();
		UndoMove(int32_t _move, const Board& pos);
};
/**
	@brief This namespace stores flags used to extract parameters from a move.
*/
namespace MoveFlags
{
	constexpr int32_t SQ = 0x7F;
	constexpr int32_t EP = 0x40000;
	constexpr int32_t PS = 0x80000;
	constexpr int32_t CA = 0x1000000;
	constexpr int32_t CAP = 0x7C000;
	constexpr int32_t PROM = 0xF00000;
}

/**
<pre>
	Internal representation of moves
	0000 0000 1 1111 1 1111 1111111 1111111 
	          ^   ^  ^   ^      ^       ^
              1   2  3   4      5       6
    1. Castle
    2. Promoted piece
    3. EnPassant
    4. Captured piece
    5. To square
    6. From square
   </pre>
 */
class Move
{
public:
	uint32_t move;
	int32_t score;
	Move(uint32_t from, uint32_t to, uint32_t captured, uint32_t prom, uint32_t flag) noexcept;
	Move(uint32_t _move, int32_t _score) noexcept;
	Move(uint32_t _move) noexcept;
	Move(const Move& o) noexcept;
	Move(Move&& o) noexcept;
	Move() noexcept;

/**
	@brief Gets the square that the move is starting from.
	@param None
	@return The source square
 */
	constexpr uint32_t from() const { return this->move & MoveFlags::SQ; }
/**
	@brief Gets the square that the move is ending on.
	@param None
	@return The destination square
 */
	constexpr uint32_t to() const { return (this->move >> 7) & MoveFlags::SQ; }
/**
	@brief Gets the piece That was captured.
	@param None
	@return The piece that was captured.
 */
	constexpr uint32_t captured() const { return (this->move >> 14) & 0xf; }
/**
	@brief Checks if the move was an EnPassant move.
	@param None
	@return true if there was EnPassant, false otherwise.
 */
	constexpr uint32_t enPassant() const {  return this->move & MoveFlags::EP; }
/**
	@brief Checks if the move was a pawn start (pawn double move).
	@param None
	@return true if there was a pawn start, false otherwise.
 */
	constexpr uint32_t pawnStart() const { return this->move & MoveFlags::PS; }
/**
	@brief Gets the piece that was promoted to if any.
	@param None
	@return The piece that was promoted to if any.
 */
	constexpr uint32_t promoted() const { return (this->move & MoveFlags::PROM) >> 20; }
/**
	@brief Checks if the move was a castle move.
	@param None
	@return true if there was a castle move, false otherwise.
 */
	constexpr uint32_t castle() const { return this->move & MoveFlags::CA; }
	
/**
	@brief Checks if the move was NULLMOVE.
	@param None
	@return true if (*this) == NULLMOVE, false otherwise.
 */
	constexpr bool isNull() const { return this->move == 0; }
/**
	@brief Checks if the move was a capture.
	@param None
	@return true if there was a capture, false otherwise.
 */
	constexpr bool wasCapture() const { return this->move & MoveFlags::CAP; }
/**
	@brief Checks if the move was a promotion.
	@param None
	@return true if there was a promotion, false otherwise.
 */
	constexpr bool wasPromotion() const { return this->move & MoveFlags::PROM; }

/**
	@brief Gets the string representation of a move (e.g "e2e4").
	@param None
	@return The string representation of a move.
 */
	const std::string toString() const noexcept;

	Move& operator=(const Move& o) noexcept;
	Move& operator=(Move&& o) noexcept;
	bool operator==(const Move& rhs) const noexcept;
	bool operator!=(const Move& rhs) const noexcept;
};

#endif
