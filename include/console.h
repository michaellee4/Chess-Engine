#ifndef CONSOLE_H
#define CONSOLE_H

#include"board.h"
#include "searchinfo.h"
#include "search.h"

class ConsoleManager
{
	Board pos;
	SearchInfo info;
	SearchAgent sa;
public:
	void consoleLoop();
	bool isOver();
	ConsoleManager() noexcept;
};


#endif