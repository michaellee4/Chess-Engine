/**
*	@file protocol.h
*	@brief Contains declaration of base class for default protocal functionality.
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "board.h"
#include "searchinfo.h"
#include "search.h"
#include "movemaker.h"

class ProtocolManager
{
protected:
	Board pos;
	SearchInfo info;
	SearchAgent sa;
public:
	static constexpr int32_t kUCI = 0;
	static constexpr int32_t kXBoard = 1;
	static constexpr int32_t kConsole = 2;
/**
	@brief Starts the protocol loop.
	@param None
	@return None
 */
	virtual void loop() = 0;

/**
	@brief Checks if the engine has recieved a stop signal from the GUI.
	@param None
	@return true if a stop command has been sent, false otherwise
 */
	virtual bool isOver() { return this->info.quit; }

/**
	@brief Returns the protocol identifier for the current protocol.
	@param None
	@return The protocol identifier
 */
	virtual int32_t getProtocol() = 0;
	
	ProtocolManager() : pos(), info(), sa() {}
	virtual ~ProtocolManager() {};



};

#endif