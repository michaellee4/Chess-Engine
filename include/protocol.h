#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "board.h"
#include "searchinfo.h"
#include "search.h"

class ProtocolManager
{
protected:
	Board pos;
	SearchInfo info;
	SearchAgent sa;
	// Current mode
	enum { UCI_MODE, XBOARD_MODE, CONSOLE_MODE};
public:
	virtual void loop() = 0;
	virtual bool isOver() { return this->info.quit; }
	virtual int32_t getProtocol() = 0;
	ProtocolManager(): pos(), info(), sa() {}
	virtual ~ProtocolManager() {};



};

#endif