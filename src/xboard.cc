/**
*	@file xboard.cc
*	@brief Contains definitions of functions declared in xboard.h.
*	@author Michael Lee
*	@date 1/9/2019
*/
#include "xboard.h"
#include "io.h"
#include "stopwatch.h"
#include <iostream>
#include <sstream>
#include <cstdio>
#include "searchinfo.h"

XBoardManager::XBoardManager() noexcept : ProtocolManager() { info.protocol = ProtocolManager::kXBoard;}

XBoardManager::~XBoardManager() noexcept = default;

void XBoardManager::loop()
{
	info.doPrint = true;
	std::cout << "feature ping=1 setboard=1 colors=0 usermove=1" << std::endl;
	std::cout << "feature done=1" << std::endl;

	int32_t depth = -1;
	std::vector<int32_t> movesToGo { 30, 30 };
	int32_t moveTime = -1;
	int64_t time = -1;
	int64_t inc = 0;
	int32_t engineSide = BLACK;
	int32_t mps = 0;
	int timeLeft;   
	int sec = 0;

	std::string buf;
	std::string cmd;
	while (true)
	{
		std::cout << std::flush;
		if(this->pos.side_to_move == static_cast<unsigned>(engineSide) && !sa.isGameOver(this->pos))
		{
			this->info.startTime = Stopwatch::getTimeInMilli();
			this->info.depth = depth;
			if(time != -1)
			{
				this->info.timeLimit = true;
				time /= movesToGo[pos.side_to_move];
				time -= 50;
				this->info.stopTime = this->info.startTime + time + inc;
			}
			if(depth == -1 || depth > static_cast<signed>(kMaxSearchDepth))
			{
				this->info.depth = kMaxSearchDepth;
			}
			std::cout<<"time:"<<time<<" start:"<<this->info.startTime<<" stop:"<<this->info.stopTime<<" depth:"<<this->info.depth<<" timeset:"<<this->info.timeLimit<<" movestogo:"<<movesToGo[pos.side_to_move]<<" mps"<<mps<<'\n';
			sa.searchPosition(pos, info);
			if(mps != 0)
			{
				movesToGo[!pos.side_to_move]--;
				if(movesToGo[!pos.side_to_move] < 1)
				{
					movesToGo[!pos.side_to_move] = mps;
				}
			}
		}	
		if(!(getline (std::cin, buf))) { continue; }
		std::stringstream ss(buf);
		ss >> buf;
		if (buf == "quit") 
		{
			this->info.quit = true;
			break;
		}
		else if (buf == "force")
		{
			engineSide = BOTH;
		}
		else if (buf == "protover")
		{
			std::cout << "feature ping=1 setboard=1 colors=0 usermove=1" << std::endl;
			std::cout << "feature done=1" << std::endl;
		}
		else if(buf == "sd")
		{
			ss >> depth;
		}
		else if (buf == "st")
		{
			ss >> moveTime;
		}
		else if (buf == "time")
		{
			ss >> time;
			time *= 10;
		}
		else if (buf == "level")
		{
			sec = 0;
			moveTime = -1;
			ss >> mps;
			ss >> timeLeft;
			if(ss.peek() == ':')
			{
				char tmp;
				ss >> tmp;
				ss >> sec;
				ss >> inc;
			}
			else
			{
				ss >> inc;
			}
			timeLeft*= Stopwatch::kMilliPerSecond * Stopwatch::kSecondsPerMinute;
			timeLeft+= sec * Stopwatch::kMilliPerSecond;
			movesToGo[0] = movesToGo[1] = 30;
			if(mps != 0)
			{
				movesToGo[0] = movesToGo[1] = mps;	
			}
			time = -1;
		}
		else if (buf == "ping")
		{
			ss >> buf;
			std::cout<<"pong"<<buf<<std::endl;
		}
		else if (buf == "new")
		{
			engineSide = BLACK;
			this->pos.parseFEN(STARTFEN);
			depth = -1;
			time = -1;
		}
		else if (buf == "setboard")
		{
			engineSide = BOTH;
			std::stringstream fen;
			ss >> buf;
			while(ss.good() && buf != "moves")
			{
				fen << buf << ' ';
				ss >> buf;
			}
			fen << buf;
			this->pos.parseFEN(fen.str());
		}
		else if(buf == "go")
		{
			engineSide = this->pos.side_to_move;
		}
		else if(buf == "usermove")
		{
			movesToGo[pos.side_to_move]--;
			ss >> buf;
			Move move = IO::parseMove(buf, this->pos);
			if(move.isNull()) { continue; }
			MM::makeMove(pos, move);
			this->pos.ply = 0;
		}
	}
}

int32_t XBoardManager::getProtocol()
{
	return ProtocolManager::kXBoard;
}