#ifndef MOVEMAKER_H
#define MOVEMAKER_H

#include "defs.h"
#include "board.h"

#define HASH_PCE(pce,sq) (pos.pos_key ^= (PieceKeys[(pce)][(sq)]))
#define HASH_CA (pos.pos_key ^= (CastleKeys[(pos.castle_perm)]))
#define HASH_SIDE (pos.pos_key ^= (SideKey))
#define HASH_EP (pos.pos_key ^= (PieceKeys[EMPTY][(pos.en_pas)]))

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
    static void ClearPiece(const uint32_t sq, Board& pos);
    static void AddPiece(const uint32_t sq, Board& pos, const uint32_t pce);
    static void MovePiece(const uint32_t src, const uint32_t dest, Board& pos);
public:
    static bool MakeMove(Board& pos, Move moveInfo);
    static void TakeMove(Board& pos);
    
};


#endif
