/**
*	@file move.cc
*	@brief Contains definitions of functions declared in move.h.
*	@author Michael Lee
*	@date 1/9/2019
*/
#include "move.h"
#include "defs.h"
#include "board.h"
#include "utils.h"
#include<iostream>
#include <sstream>
#include <utility>

/*** UMOVE ***/
UndoMove::UndoMove() : move(0), castle_perm(0), en_pas(NO_SQ), fifty_move(0), pos_key(0) {}

UndoMove::UndoMove(int32_t _move, const Board& pos) : move(_move), castle_perm(pos.castle_perm), en_pas(pos.en_pas), fifty_move(pos.fifty_move), pos_key(pos.pos_key) {}

/*** MOVE ***/
Move::Move(uint32_t from, uint32_t to, uint32_t captured, uint32_t prom, uint32_t flag) noexcept : 
move(0 |(from & 0x7f) | ((to & 0x7f) << 7) | ((captured & 0xf) << 14) | ((prom & 0xf) << 20) | flag), 
score(0){}

Move::Move(uint32_t _move, int32_t _score) noexcept : move(_move), score(_score){}

Move::Move(uint32_t _move) noexcept : move(_move), score(0) {}

Move::Move() noexcept : move(0), score(0) {}

Move::Move(const Move& o) noexcept  = default;

Move::Move(Move&& o) noexcept : move(o.move), score(o.score){}

const std::string Move::toString() const noexcept
{
	if(this->move == 0)
	{
		return "NOMOVE";

	}
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
		{
			pChar = 'n';
		} 
		else if(promoted == wR || promoted == bR) 
		{
			pChar = 'r';
		} 
		else if(promoted == wB || promoted == bB) 
		{
			pChar = 'b';
		}
		stream << pChar;
	}
  	return stream.str();
}

Move& Move::operator=(const Move& o) noexcept
{
	if(this != &o)
	{
		this->move = o.move;
		this->score = o.score;
	}
	return *this;
}

Move& Move::operator=(Move&& o) noexcept
{
	if(this != &o)
	{
		this->move = o.move;
		this->score = o.score;
	}
	return *this;
}

bool Move::operator==(const Move& rhs) const noexcept
{
	return this->move == rhs.move;
}

bool Move::operator!=(const Move& rhs) const noexcept
{
	return this->move != rhs.move;
}