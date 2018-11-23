#ifndef UTILS_H
#define UTILS_H

#include "defs.h"
#include "board.h"
#include <string>
int FileRankToSq(int file, int rank);
uint64_t RandU64();
bool IsPiece(int piece);
void ShowSqAtBySide(const int side,Board& pos);
std::string SqToString(const int sq);
#endif