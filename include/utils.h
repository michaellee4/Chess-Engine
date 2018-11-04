#ifndef UTILS_H
#define UTILS_H

#include "defs.h"
#include "board.h"
#include <string>
int FileRankToSq(int file, int rank);
U64 RandU64();

void ShowSqAtBySide(const int side,Board& pos);
#endif