#ifndef UTILS_H
#define UTILS_H

#include "defs.h"
#include "board.h"
#include "searchinfo.h"
#include <string>

// returns the SQ# on the 120 Sq board representation
int fileRankToSq(int file, int rank);

// generates a random 64 bit integer
uint64_t randU64();

bool isPiece(int piece);

// prints the 8x8 board with numbers indicating how many times each sq is attacked by the provided side
void showAttackedSqs(const int side,Board& pos);

// String representation of a square
std::string sqToString(const int sq);

void stringToLower(std::string& str);

int InputWaiting();

void ReadInput(SearchInfo& info);

#endif

