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