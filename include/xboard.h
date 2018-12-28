#ifndef XBOARD_H
#define XBOARD_H
#include"board.h"
#include "searchinfo.h"
#include "search.h"
#include<string>
class XBoardManager
{
	Board pos;
	SearchInfo info;
	SearchAgent sa;
public:
	void XBoardLoop();
	XBoardManager();
};

#endif