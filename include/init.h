#ifndef INIT_H
#define INIT_H

namespace Init
{
	void initAll();

	// creates 2 arrays to map 64 <-> 120 board square representations
	void initSq120ToSq64();

	// initializes bitmasks used in bitboards.cc
	void initBitMasks();

	// initializes all necessary hash codes for position hashes
	void initHashKeys();

	// initializes the two arrays to return a given square's file and rank
	void initFileRankBrd();	

	// initializes the MvvLva arrays
	void initMvvLva();
}


#endif