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
public:
	virtual void loop() = 0;
	virtual bool isOver() { return this->info.quit; }
	ProtocolManager(): pos(), info(), sa() {}
	virtual ~ProtocolManager() {};


};

#endif