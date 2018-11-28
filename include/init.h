#ifndef INIT_H
#define INIT_H

void InitAll();

// creates 2 arrays to map 64 <-> 120 board square representations
void InitSq120ToSq64();

// initializes bitmasks used in bitboards.cc
void InitBitMasks();

// initializes all necessary hash codes for position hashes
void InitHashKeys();

// initializes the two arrays to return a given square's file and rank
void InitFileRankBrd();

#endif