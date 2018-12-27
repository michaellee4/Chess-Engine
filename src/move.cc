#include "move.h"
#include <sstream>
#include "defs.h"
#include<iostream>
#include "board.h"
#include <utility>
/*** UMOVE ***/
U_Move::U_Move() : move(0), castlePerm(0), enPas(NO_SQ), fiftyMove(0), pos_key(0) {}
U_Move::U_Move(int32_t _move, const Board& pos) : move(_move), castlePerm(pos.castle_perm), enPas(pos.en_pas), fiftyMove(pos.fifty_move), pos_key(pos.pos_key) {}

/*** MOVE ***/
Move::Move(uint32_t from, uint32_t to, uint32_t captured, uint32_t prom, uint32_t flag): 
move(0 |(from & 0x7f) | ((to & 0x7f) << 7) | ((captured & 0xf) << 14) | ((prom & 0xf) << 20) | flag), 
score(0){}

Move::Move(uint32_t _move, int32_t _score) : move(_move), score(_score){}

Move::Move(uint32_t _move) : move(_move), score(0) {}

Move::Move() : move(0), score(0) {}

Move::Move(const Move& o) : move(o.move), score(o.score){}

Move::Move(Move&& o) noexcept : move(std::move(o.move)), score(std::move(o.score)){}

std::string Move::toString()
{
	char srcFile = 'a' + BoardUtils::FileBrd[this->from()];
	char srcRank = '1' + BoardUtils::RankBrd[this->from()];
	char destFile = 'a' + BoardUtils::FileBrd[this->to()];
	char destRank = '1' + BoardUtils::RankBrd[this->to()];
	int promoted = this->promoted();
	std::ostringstream stream;
	stream << srcFile << srcRank << destFile << destRank;
	if(promoted)
	{
		char pChar = 'q';
		if(promoted == wN || promoted == bN)
			pChar = 'n';
		else if(promoted == wR || promoted == bR)
			pChar = 'r';
		else if(promoted == wB || promoted == bB)
			pChar = 'b';
		stream << pChar;
	}
	
  	return stream.str();
}

Move& Move::operator=(const Move& o)
{
	if(this != &o)
	{
		this->move = o.move;
		this->score = o.score;
	}
	return *this;
}

Move& Move::operator=(Move&& o)
{
	if(this != &o)
	{
		this->move = std::move(o.move);
		this->score = std::move(o.score);
	}
	return *this;
}

bool Move::operator==(const Move& rhs) const
{
	return this->move == rhs.move;
}

bool Move::operator!=(const Move& rhs) const
{
	return this->move != rhs.move;
}