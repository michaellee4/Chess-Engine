#ifndef UTILS_H
#define UTILS_H

#include "defs.h"
#include "board.h"
#include <string>

// returns the SQ# on the 120 Sq board representation
int FileRankToSq(int file, int rank);

// Generates a random 64 bit integer
uint64_t RandU64();

bool IsPiece(int piece);

// Prints the 8x8 board with numbers indicating how many times each sq is attacked by the provided side
void ShowSqAtBySide(const int side,Board& pos);

// String representation of a square
std::string SqToString(const int sq);
#endif