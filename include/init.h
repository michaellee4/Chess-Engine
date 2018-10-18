#ifndef INIT_H
#define INIT_H

void InitAll();

// creates 2 arrays to map 64 <-> 120 board square representations
void InitSq120ToSq64();
void InitBitMasks();
void InitHashKeys();

#endif