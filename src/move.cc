#include "move.h"
#include <sstream>
#include "defs.h"
#include<iostream>

Move::Move(uint32_t from, uint32_t to, uint32_t captured, uint32_t prom, uint32_t flag): 
move(0 |(from & 0x7f) | ((to & 0x7f) << 7) | ((captured & 0xf) << 14) | ((prom & 0xf) << 20) | flag), 
score(0){}

Move::Move(uint32_t move, int32_t score) : move(move), score(score){}

Move::Move(uint32_t move) : move(move), score(0) {}

Move::Move()
{
	this->move = this->score = 0;
}

uint32_t Move::from()
{
	return this->move & 0x7f;
}
uint32_t Move::to()
{
	return (this->move >> 7) & 0x7f; 
}
uint32_t Move::captured()
{
	return (this->move >> 14) & 0xf; 
}
uint32_t Move::enPassant()
{
	return this->move & 0x40000;
}
uint32_t Move::pawnStart()
{
	return this->move & 0x80000; 
}
uint32_t Move::promoted()
{
	return (this->move >> 20) & 0xf;
}
uint32_t Move::castle()
{
	return this->move & 0x1000000;
}
bool Move::wasCapture()
{
	return this->move & 0x7c000;
}
bool Move::wasPromotion()
{
	return this->move & 0xf00000;
}
std::string Move::toString()
{
	char srcFile = 'a' + FileBrd[this->from()];
	char srcRank = '1' + RankBrd[this->from()];
	char destFile = 'a' + FileBrd[this->to()];
	char destRank = '1' + RankBrd[this->to()];
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

bool Move::isNull()
{
	return this->move == 0; 
}
