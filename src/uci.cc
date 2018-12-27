#include "uci.h"
#include "defs.h"
#include "io.h"
#include "move.h"
#include <iostream>
#include <sstream>

void parseGoCmd(const std::string& cmd, SearchInfo& info, Board& pos)
{
(void)pos;
(void)cmd;
(void)info;
}

void parsePosition(const std::string& input, Board& pos)
{

	std::stringstream ss(input);
	std::string buf;

	ss >> buf;
	ASSERT(buf == "position");

	if(input.substr(0,UCI_STARTPOS.size()) == UCI_STARTPOS)
	{
		pos.parseFEN(STARTFEN);
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
			pos.parseFEN(STARTFEN);
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
			pos.parseFEN(fen.str());
		}
	}

	if(buf == "moves")
	{
		//reads all the moves and makes them 1 by 1
		while(ss >> buf)
		{
			Move m = IO::parseMove(buf, pos);
			if(m == NOMOVE) { break; }
			MM::makeMove(pos, m);
			pos.ply = 0;
		}
	}
	IO::printBoard(pos);
}

void UCILoop()
{
	std::string buf;
	std::cout << "id name ChessEngine\n";
	std::cout << "id author ml45898\n";
	std::cout << "uciok\n";
	Board pos;
	SearchInfo info;

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
			parsePosition(buf, pos);
		}
		else if(firstWord == "ucinewgame")
		{
			parsePosition(UCI_STARTPOS, pos);
		}
		else if(firstWord == "go")
		{
			parseGoCmd(buf, info, pos);
		}
		else if (firstWord == "quit")
		{
			info.quit = true;
		}
		else if (firstWord == "uci")
		{
			std::cout << "id name ChessEngine\n";
			std::cout << "id author ml45898\n";
			std::cout << "uciok\n";	
		}
		if(info.quit) { break; }
	}
}