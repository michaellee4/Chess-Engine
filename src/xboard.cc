#include "xboard.h"
#include "io.h"
#include "stopwatch.h"
#include <iostream>
#include <sstream>
#include <cstdio>
XBoardManager::XBoardManager() : pos(), info(), sa() {}

void XBoardManager::XBoardLoop()
{
	info.GAME_MODE = XBOARD_MODE;
	info.POST_THINKING = true;

	std::cout << "feature ping=1 setboard=1 colors=0 usermove=1" << std::endl;
	std::cout << "feature done=1" << std::endl;

	std::string buf;
	std::string cmd;
	int32_t depth = -1;
	std::vector<int32_t> movesToGo { 30, 30 };
	int32_t moveTime = -1;
	int64_t time = -1;
	int64_t inc = 0;
	int32_t engineSide = BLACK;
	int32_t mps = 0;
	int timeLeft;   
	int sec;
	// int32_t score;
	while (true)
	{
		std::cout << std::flush;
		if(this->pos.side_to_move == (unsigned)engineSide && sa.isGameOver(this->pos) == false)
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
			if(depth == -1 || depth > (signed)MAX_DEPTH)
			{
				this->info.depth = MAX_DEPTH;
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
		std::cout << "command seen:" << buf <<std::endl;

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
			std::cout << "DEBUG depth: "<< depth <<std::endl; 
		}
		else if (buf == "st")
		{
			ss >> moveTime;
			std::cout << "DEBUG moveTime: "<< moveTime <<std::endl; 
		}
		else if (buf == "time")
		{
			ss >> time;
			time *= 10;
			std::cout << "DEBUG time: "<< time <<std::endl; 
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
				std::cout << "DEBUG level with :" <<std::endl; 
			}
			else
			{
				ss >> inc;
				std::cout << "DEBUG level without :" <<std::endl; 
			}
			timeLeft*= 60000;
			timeLeft+= sec * 1000;
			movesToGo[0] = movesToGo[1] = 30;
			if(mps != 0)
			{
				movesToGo[0] = movesToGo[1] = mps;	
			}
			time = -1;
		    printf("DEBUG level timeLeft:%d movesToGo:%d inc:%ld mps%d\n",timeLeft,movesToGo[0],inc,mps);
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
			ss >> buf;
			this->pos.parseFEN(buf);
		}
		else if(buf == "go")
		{
			engineSide = this->pos.side_to_move;
		}
		else if(buf == "usermove")
		{
			ss >> buf;
			movesToGo[pos.side_to_move]--;
			Move move = IO::parseMove(buf, this->pos);
			if(move == NOMOVE) { continue; }
			MM::makeMove(pos, move);
			this->pos.ply = 0;
		}
	}
}
