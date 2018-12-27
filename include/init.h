#ifndef INIT_H
#define INIT_H

namespace Init
{
	void initAll() noexcept;

	// creates 2 arrays to map 64 <-> 120 board square representations
	void initSq120ToSq64() noexcept;

	// initializes bitmasks used in bitboards.cc
	void initBitMasks() noexcept;

	// initializes all necessary hash codes for position hashes
	void initHashKeys() noexcept;

	// initializes the two arrays to return a given square's file and rank
	void initFileRankBrd() noexcept;	

	// initializes the MvvLva arrays
	void initMvvLva() noexcept;
}


#endif