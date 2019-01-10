/**
*	@file xboard.h
*	@brief Contains declarations for the XBoard protocol.
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef XBOARD_H
#define XBOARD_H
#include "protocol.h"

/**
 * See ProtocolManager documentation
 */
class XBoardManager : public ProtocolManager
{
public:
	void loop() override;
	int32_t getProtocol() override;
	XBoardManager() noexcept;
	~XBoardManager() noexcept;
};

#endif