#include "uci.h"
#include "defs.h"
#include "io.h"
#include "move.h"
#include "utils.h"
#include "stopwatch.h"
#include <iostream>
#include <sstream>


UCIManager::UCIManager() : pos(), info(), sa() {}
// go depth 6 wtime 180000 btime 100000 binc 1000 winc 1000 movetime 1000 movestogo 40
void UCIManager::parseGoCmd(const std::string& input)
{
	int32_t depth = -1;
	int32_t movesToGo = 30;
	int32_t moveTime = -1;
	int64_t time = -1;
	int64_t inc = 0;
	this->info.timeLimit = false;
	std::string buf;
	std::stringstream ss(input);
	while(ss.good())
	{
		ss >> buf;
		if(buf == "binc" && this->pos.side_to_move == BLACK)
		{
			ss >> inc;
		}
		else if (buf == "winc" && this->pos.side_to_move == WHITE)
		{
			ss >> inc;
		}
		else if(buf == "btime" && this->pos.side_to_move == BLACK)
		{
			ss >> time;
		}
		else if(buf == "wtime" && this->pos.side_to_move == WHITE)
		{
			ss >> time;
		}
		else if(buf == "movestogo")
		{
			ss >> movesToGo;
		}
		else if(buf == "movetime")
		{
			ss >> moveTime;
		}
		else if(buf == "depth")
		{
			ss >> depth;
		}
		if(moveTime != -1) 
		{
			time = moveTime;
			movesToGo = 1;
		}
	}
	this->info.startTime = Stopwatch::getTimeInMilli();
	this->info.depth = depth;
	if(time != -1) 
	{
		this->info.timeLimit = true;
		time /= movesToGo;
		time -= 50;
		this->info.stopTime = this->info.startTime + time + inc;
	}
	if(depth == -1) 
	{
		this->info.depth = MAX_DEPTH;
	}
	std::cout<<"time:"<<time<<" start:"<<this->info.startTime<<" stop:"<<this->info.stopTime<<" depth:"<<this->info.depth<<" timeset:"<<this->info.timeLimit<<'\n';
	sa.searchPosition(this->pos, this->info);
}

void UCIManager::parsePosition(const std::string& input)
{

	std::stringstream ss(input);
	std::string buf;

	ss >> buf;
	ASSERT(buf == "position");

	if(input.substr(0,UCI_STARTPOS.size()) == UCI_STARTPOS)
	{
		this->pos.parseFEN(STARTFEN);
		ss >> buf;
		ASSERT(buf == "startpos");

		// buf == moves || buf == NULL
		ss >> buf;
	}
	else
	{
		// buf == "fen"
		ss>>buf;
		if(buf != "fen")
		{
			this->pos.parseFEN(STARTFEN);
		}
		else
		{
			// builds up the fen by reading fen parameters 1 by 1 until "moves" or the end of string is found
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
	}

	if(buf == "moves")
	{
		//reads all the moves and makes them 1 by 1
		while(ss >> buf)
		{
			Move m = IO::parseMove(buf, this->pos);
			if(m == NOMOVE) { break; }
			MM::makeMove(this->pos, m);
			this->pos.ply = 0;
		}
	}
	IO::printBoard(this->pos);
}

void UCIManager::UCILoop()
{
	std::string buf;
	std::cout << "id name "<<NAME<<'\n';
	std::cout << "id author ml45898\n";
	std::cout << "uciok\n";

	while(true)
	{
		buf.clear();
		std::cout<<std::flush;
		if(!(getline (std::cin, buf))) { continue; }
		if(buf == "\n") { continue; }

		std::string firstWord = buf.substr(0, buf.find(" "));
		if(firstWord == "isready")
		{
			std::cout << "readyok\n";
			continue;
		}
		else if(firstWord == "position")
		{
			parsePosition(buf);
		}
		else if(firstWord == "ucinewgame")
		{
			parsePosition(UCI_STARTPOS);
		}
		else if(firstWord == "go")
		{
			parseGoCmd(buf);
		}
		else if (firstWord == "quit")
		{
			this->info.quit = true;
		}
		else if (firstWord == "uci")
		{
			std::cout << "id name "<< NAME<< '\n';
			std::cout << "id author ml45898\n";
			std::cout << "uciok\n";	
		}
		if(this->info.quit) { break; }
	}
}