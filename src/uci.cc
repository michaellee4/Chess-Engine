#include "uci.h"
#include <iostream>

void parseGoCmd(const std::string& cmd, SearchInfo& info, Board& pos)
{
(void)pos;
(void)cmd;
(void)info;
}

void parsePosition(const std::string& input, Board& pos)
{
(void)pos;
(void)input;
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
		if(!(std::cin>>buf)) { continue; }
		if(buf == "\n") { continue; }

		if(buf == "isready")
		{
			std::cout << "readyok\n";
			continue;
		}
		else if(buf == "position")
		{
			parsePosition(buf, pos);
		}
		else if(buf == "ucinewgame")
		{
			const std::string goStr = "position startpos\n";
			parsePosition(goStr, pos);
		}
		else if(buf == "go")
		{
			parseGoCmd(buf, info, pos);
		}
		else if (buf == "quit")
		{
			info.quit = true;
		}
		else if (buf == "uci")
		{
			std::cout << "id name ChessEngine\n";
			std::cout << "id author ml45898\n";
			std::cout << "uciok\n";	
		}
		if(info.quit) { break; }
	}
}