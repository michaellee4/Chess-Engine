/**
*	@file init.h
*	@brief Contains declarations of functions that fill the non static constant arrays used throughout the engine.
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef INIT_H
#define INIT_H

namespace Init
{
	/**
	 * Input: None
	 * Output: None
	 * Operation: Calls all of the 'init' methods below
	 */
	void initAll() noexcept;

	/**
	 * Input: None
	 * Output: None
	 * Operation: Fills in the arrays that convert between array-120 to array-64 representations
	 */
	void initSq120ToSq64() noexcept;

	/**
	 * Input: None
	 * Output: None
	 * Operation: Fills in the arrays used for setting/clearing bits in bitboards
	 */
	void initBitMasks() noexcept;

	/**
	 * Input: None
	 * Output: None
	 * Operation: Fills in the hashkeys arrays that will be used to for getting the board's hashkey
	 */
	void initHashKeys() noexcept;

	/**
	 * Input: None
	 * Output: None
	 * Operation: Fills in the arrays that return the file/rank # for a given square
	 */
	void initFileRankBrd() noexcept;	

	/**
	 * Input: None
	 * Output: None
	 * Operation: Fills in the arrays used for evaluating pawn structure during evaluation
	 */
	void initEvalMasks() noexcept;

	/**
	 * Input: None
	 * Output: None
	 * Operation: Fills in the arrays to determine most valuable victim least valuable attacker priority
	 */
	void initMvvLva() noexcept;
}


#endif