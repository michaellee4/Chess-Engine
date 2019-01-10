/**
*   @file movemaker.h
*   @brief Contains declarations of functions that manipulate the position of pieces on the internal board.
*   @author Michael Lee
*   @date 1/9/2019
*/

#ifndef MOVEMAKER_H
#define MOVEMAKER_H

#include "constants.h"
#include "board.h"

/**
 * Indicates the change in castle permissions if a given square moves.
 * Used with bitwise &
 */
constexpr std::array<int32_t,120> CastlePerm {
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15,  7, 15, 15, 15,  3, 15, 15, 11, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};


class MM
{
/**
    @brief Removes the piece on the given square from the internal board representation.
    @param sq The square to clear.
    @param pos The current board state.
    @return None
 */
    static void clearPiece(const uint32_t sq, Board& pos) noexcept;
/**
    @brief Adds the piece on the given square to the internal board representation
    @param sq The square to add the piece to.
    @param pos The current board state.
    @param pce The piece to add to the target square
    @return None
 */
    static void addPiece(const uint32_t sq, Board& pos, const uint32_t pce) noexcept;
/**
    @brief Moves the piece from the source square to the dest square and performs capture if applicable
    @param src The square the piece starts on.
    @param dest The square the piece is moving to.
    @param pos The current board state.
    @return None
 */
    static void movePiece(const uint32_t src, const uint32_t dest, Board& pos) noexcept;
public:
/**
    @brief Makes the provided move (move piece/capture/update board)
    @param pos The current board state.
    @return true if move was successfully made (legal), false otherwise
 */
    static bool makeMove(Board& pos, const Move& moveInfo) noexcept;
/**
    @brief Undos the last move that was made which is stored in Board::history.
    @param pos The current board state.
    @return None
 */
    static void takeMove(Board& pos) noexcept;
/**
    @brief Similar in concept to Make move, but gives the opposing side a free move.
    @param pos The current board state.
    @return None
 */
    static void makeNullMove(Board& pos) noexcept;
/**
    @brief Undos the last null move.
    @param pos The current board state.
    @return None
 */
    static void takeNullMove(Board& pos) noexcept;
    
};


#endif
