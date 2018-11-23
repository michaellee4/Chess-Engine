
#ifndef MOVE_H
#define MOVE_H

//move flags
#define EP 0x40000
#define PS 0x80000
#define CA 0x1000000
#define CAP 0x7C000
#define PROM 0xF00000

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
		uint64_t posKey;
};

class Move
{
	public:
		int move;
		int score;
		Move(int from, int to, int captured, int prom, int flag);
		Move(int move, int score);
		Move(int move);
		Move();
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