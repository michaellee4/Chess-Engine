#ifndef BITBOARD_H
#define BITBOARD_H

#include "defs.h"


int PopBit(U64&);

int CountBits(U64);

void PrintBitBoard(U64);

void SetBit(U64&, int);

void ClearBit(U64&, int);
#endif