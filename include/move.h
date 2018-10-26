
#ifndef MOVE_H
#define MOVE_H

#include "defs.h"
#include <string>
// used for undoing
class U_Move
{
	public:
		int move;
		int castlePerm;
		int enPas;
		int fiftyMove;
		U64 posKey;
};

class Move
{
	public:
		int move;
		int score;

		// 7 bits for src
		int From();
		// 7 bits for dest 
		int To();
		// 4 bits for which piece was captured if any
		int Captured();
		// 1 bit for enPas
		int EnPassant();
		// 1 bit for pawn start 
		int PawnStart();
		// 4 bits for which piece was captured if any
		int Promoted();
		// 1 bit for Castle move
		int Castle();

		bool wasCapture();
		bool wasPromotion();

		std::string ToString();

};
#endif