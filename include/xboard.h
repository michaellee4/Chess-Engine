#ifndef XBOARD_H
#define XBOARD_H
#include "board.h"
#include "searchinfo.h"
#include "search.h"
#include "protocol.h"
#include <string>
class XBoardManager : public ProtocolManager
{
public:
	void loop() override;
	XBoardManager() noexcept;
	~XBoardManager() noexcept;
};

#endif