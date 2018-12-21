
#ifndef MOVE_H
#define MOVE_H

//move flags
#define EP 0x40000
#define PS 0x80000
#define CA 0x1000000
#define CAP 0x7C000
#define PROM 0xF00000

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
		uint32_t move;
		int score;
		Move(uint32_t from, uint32_t to, uint32_t captured, uint32_t prom, uint32_t flag);
		Move(uint32_t move, int32_t score);
		Move(uint32_t move);
		Move();
		// 7 bits for src
		uint32_t From();
		// 7 bits for dest 
		uint32_t To();
		// 4 bits for which piece was captured if any
		uint32_t Captured();
		// 1 bit for enPas
		uint32_t EnPassant();
		// 1 bit for pawn start 
		uint32_t PawnStart();
		// 4 bits for which piece was captured if any
		uint32_t Promoted();
		// 1 bit for Castle move
		uint32_t Castle();
		
		bool isNull();
		bool wasCapture();
		bool wasPromotion();

		std::string ToString();

};

#endif
