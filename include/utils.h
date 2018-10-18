#ifndef UTILS_H
#define UTILS_H

#include "defs.h"

int FileRankToSq(int file, int rank);
U64 RandU64();

extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];



#endif