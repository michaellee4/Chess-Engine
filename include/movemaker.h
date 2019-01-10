#ifndef MOVEMAKER_H
#define MOVEMAKER_H

#include "defs.h"
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
     * Input: The square a piece is on, a Board object
     * Output: None
     * Operation: removes the piece on the given square from the internal board representation
     * Called by Make/Take move
     */
    static void clearPiece(const uint32_t sq, Board& pos) noexcept;

    /**
     * Input: The square a piece is on, a Board object, the piece to add
     * Output: None
     * Operation: Adds the piece on the given square to the internal board representation
     * Called by Make/Take move
     */
    static void addPiece(const uint32_t sq, Board& pos, const uint32_t pce) noexcept;

    /**
     * Input: The source square, destination square, a Board object
     * Output: None
     * Operation: Moves the piece from the source square to the dest square and performs capture if applicable
     * Called by Make/Take move
     */
    static void movePiece(const uint32_t src, const uint32_t dest, Board& pos) noexcept;
public:

    /**
     * Input: Board object, Move to make
     * Output: true if move was successfully made (legal), false otherwise
     * Operation: Makes the provided move (move piece/capture/update board)
     */
    static bool makeMove(Board& pos, const Move& moveInfo) noexcept;

    /**
     * Input: a Board object
     * Output: None
     * Operation: Undos the last move that was made which is stored in Board::history
     */
    static void takeMove(Board& pos) noexcept;

    /**
     * Input: a Board object
     * Output: None
     * Operation: Similar in concept to Make move, but gives the opposing side a free move
     */
    static void makeNullMove(Board& pos) noexcept;

    /**
     * Input: a Board object
     * Output: None
     * Operation: Undos the last null move
     */
    static void takeNullMove(Board& pos) noexcept;
    
};


#endif
