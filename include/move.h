#ifndef MOVE_H
#define MOVE_H

//move flags
#define EP 0x40000
#define PS 0x80000
#define CA 0x1000000
#define CAP 0x7C000
#define PROM 0xF00000

#include <string>
class Board;
// used for undoing
class U_Move
{
	public:
		int move;
		int castlePerm;
		int enPas;
		int fiftyMove;
		uint64_t pos_key;
		U_Move();
		U_Move(int32_t move, const Board& pos);
};

class Move
{
	public:
		uint32_t move;
		int score;
		Move(uint32_t from, uint32_t to, uint32_t captured, uint32_t prom, uint32_t flag);
		Move(uint32_t move, int32_t score);
		Move(uint32_t move);
		Move(const Move& move);
		Move(Move&& move) noexcept;
		Move();
		// 7 bits for src
		inline uint32_t from() const { return this->move & 0x7f; }
		// 7 bits for dest 
		inline uint32_t to() const { return (this->move >> 7) & 0x7f; }
		// 4 bits for which piece was captured if any
		inline uint32_t captured() const { return (this->move >> 14) & 0xf; }
		// 1 bit for enPas
		inline uint32_t enPassant() const {  return this->move & 0x40000; }
		// 1 bit for pawn start 
		inline uint32_t pawnStart() const { return this->move & 0x80000; }
		// 4 bits for which piece was captured if any
		inline uint32_t promoted() const { return (this->move >> 20) & 0xf; }
		// 1 bit for Castle move
		inline uint32_t castle() const { return this->move & 0x1000000; }
		
		inline bool isNull() const { return this->move == 0; }
		inline bool wasCapture() const { return this->move & 0x7c000; }
		inline bool wasPromotion() const { return this->move & 0xf00000; }

		std::string toString();

		Move& operator=(const Move& move);


};

#endif
