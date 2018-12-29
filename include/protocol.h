#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "board.h"
#include "searchinfo.h"
#include "search.h"

class ProtocolManager
{
	Board pos;
	SearchInfo info;
	SearchAgent sa;
public:
	virtual void loop() = 0;
	constexpr bool isOver() { return this->info.quit; }
};

#endif