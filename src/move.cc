#include "move.h"
#include <sstream>
#include "defs.h"
#include<iostream>

Move::Move(int from, int to, int captured, int enpas, int ps, int prom, int castle)
{
	this->move = 0;
	this->move |= from & 0x7f;
	this->move |= (to & 0x7f) << 7;
	this->move |= (captured & 0xf) << 14;
	this->move |= enpas << 18;
	this->move |= ps << 19;
	this->move |= (prom & 0xf) << 20;
	this->move |= castle << 24;
}
Move::Move(int move, int score)
{
	this->move = move;
	this->score = score;
}
Move::Move(int move)
{
	this->move = move;
}
Move::Move()
{
	this->move = this->score = 0;
}

int Move::From()
{
	return this->move & 0x7f;
}
int Move::To()
{
	return (this->move >> 7) & 0x7f; 
}
int Move::Captured()
{
	return (this->move >> 14) & 0xf; 
}
int Move::EnPassant()
{
	return this->move & 0x40000;
}
int Move::PawnStart()
{
	return this->move & 0x80000; 
}
int Move::Promoted()
{
	return (this->move >> 20) & 0xf;
}
int Move::Castle()
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
std::string Move::ToString()
{
	char srcFile = 'a' + FileBrd[this->From()];
	char srcRank = '1' + RankBrd[this->From()];
	char destFile = 'a' + FileBrd[this->To()];
	char destRank = '1' + RankBrd[this->To()];
	int promoted = this->Promoted();
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