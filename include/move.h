
#ifndef MOVE_H
#define MOVE_H

#include "defs.h"

class U_Move
{
	public:
		int move;
		int castlePerm;
		int enPas;
		int fiftyMove;
		U64 posKey;
};

#endif