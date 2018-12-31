#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "board.h"
#include "searchinfo.h"
#include "search.h"
#include "movemaker.h"
#include "polyglot.h"

class ProtocolManager
{
protected:
	Board pos;
	SearchInfo info;
	SearchAgent sa;
	PolyBook book;
public:
	static constexpr int32_t kUCI = 0;
	static constexpr int32_t kXBoard = 1;
	static constexpr int32_t kConsole = 2;
	virtual void loop() = 0;
	virtual bool isOver() { return this->info.quit; }
	virtual int32_t getProtocol() = 0;
	ProtocolManager(): pos(), info(), sa(), book() 
	{
		book.readBook();
	}
	virtual ~ProtocolManager() {};



};

#endif