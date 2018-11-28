#ifndef MOVEMAKER_H
#define MOVEMAKER_H

#include "defs.h"
#include "board.h"

// Indicates the change in castle permissions for a given Sq move. Used with bitwise &
const int CastlePerm[120] = {
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
	// Used by Make/Take move to manipulate the board for a move
    static void ClearPiece(const uint32_t sq, Board& pos);
    static void AddPiece(const uint32_t sq, Board& pos, const uint32_t pce);
    static void MovePiece(const uint32_t src, const uint32_t dest, Board& pos);
public:
	// Makes the provided move (move piece/capture/update board)
    static bool MakeMove(Board& pos, Move moveInfo);

    // Undo's the last move made which is stored in Board::hist_move
    static void TakeMove(Board& pos);
    
};


#endif
