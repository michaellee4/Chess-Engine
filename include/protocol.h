#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "board.h"
#include "searchinfo.h"
#include "search.h"
#include "movemaker.h"

/**
 * This class serves as a base class
 * that details the basic functionality
 * of the various protocols
 */
class ProtocolManager
{
protected:
	Board pos;
	SearchInfo info;
	SearchAgent sa;
public:
	/**
	 * Protocol identifiers
	 */
	static constexpr int32_t kUCI = 0;
	static constexpr int32_t kXBoard = 1;
	static constexpr int32_t kConsole = 2;

	/**
	 * Input: None
	 * Output: None
	 * Operation: Starts the game loop
	 */
	virtual void loop() = 0;

	/**
	 * Input: None
	 * Output: true if a stop command has been sent by the user/Arena
	 *  	   false otherwise
	 * Operation: None
	 */
	virtual bool isOver() { return this->info.quit; }

	/**
	 * Input: None
	 * Output: The protocol identifier of the derived class
	 * Operation: None
	 */
	virtual int32_t getProtocol() = 0;
	
	ProtocolManager() : pos(), info(), sa() {}
	virtual ~ProtocolManager() {};



};

#endif