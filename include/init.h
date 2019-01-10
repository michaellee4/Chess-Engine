/**
*	@file init.h
*	@brief Contains declarations of functions that fill the non static constant arrays used throughout the engine.
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef INIT_H
#define INIT_H


/**
	@brief Provides methods to initialize the non constant arrays used throughout the engine
 */
namespace Init
{

/**
	@brief Calls all of the other 'init' methods.
	@param None
	@return None.
 */
	void initAll() noexcept;

/**
	@brief Fills in the arrays that convert between array-120 to array-64 representations.
	@param None
	@return None.
 */
	void initSq120ToSq64() noexcept;

/**
	@brief Fills in the arrays used for setting/clearing bits in bitboards.
	@param None
	@return None.
 */
	void initBitMasks() noexcept;

/**
	@brief Fills in the hashkeys arrays that will be used to for getting the board's hashkey.
	@param None
	@return None.
 */
	void initHashKeys() noexcept;

/**
	@brief Fills in the arrays that return the file/rank # for a given square.
	@param None
	@return None.
 */
	void initFileRankBrd() noexcept;	

/**
	@brief Fills in the arrays used for evaluating pawn structure during evaluation.
	@param None
	@return None.
 */
	void initEvalMasks() noexcept;

/**
	@brief Fills in the arrays to determine most valuable victim least valuable attacker priority.
	@param None
	@return None.
 */
	void initMvvLva() noexcept;
}


#endif