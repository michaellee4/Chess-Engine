#ifndef BITBOARD_H
#define BITBOARD_H

#include "defs.h"

extern const int BitTable[64];

int PopBit(U64&);

int CountBits(U64);

void PrintBitBoard(U64);

#endif