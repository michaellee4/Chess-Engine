/**
*	@file console.cc
*	@brief Contains definitions of functions declared in console.h.
*	@author Michael Lee
*	@date 1/9/2019
*/
#include "console.h"
#include "stopwatch.h"
#include "constants.h"
#include "movemaker.h"
#include "io.h"
#include "searchinfo.h"
#include "polyglot.h"
#include "engine.h"
#include <iostream>
#include <sstream>

ConsoleManager::ConsoleManager() noexcept : ProtocolManager() { info.protocol = ProtocolManager::kConsole;}

ConsoleManager::~ConsoleManager() noexcept = default;

void ConsoleManager::loop()
{
	std::cout << "\nConsole Mode! \n";
	std::cout << "Type help for commands \n";

	info.doPrint = true;
	int32_t depth = 5;
	std::vector<int32_t> movesToGo { 30, 30 };
	int32_t moveTime = 10 * Stopwatch::kMilliPerSecond;
	uint32_t engineSide = BLACK;

	std::string buf;
	std::string cmd;
	while(true)
	{
		std::cout<<std::flush;
		if(this->pos.side_to_move == engineSide && !sa.isGameOver(this->pos))
		{
			this->info.startTime = Stopwatch::getTimeInMilli();
			this->info.depth = depth;
			if(moveTime != 0)
			{
				this->info.timeLimit = true;
				this->info.stopTime = info.startTime + moveTime;
			}
			sa.searchPosition(pos, this->info);
		}

		std::cout << '\n'<<kAppName<<" > " << std::flush;

		if(!(getline (std::cin, buf))) { continue; }
		if(buf == "\n") { continue; }

		std::stringstream ss(buf);
		ss >> buf;

		if(buf == "help")
		{
			std::cout << ("Commands:\n");
			std::cout << ("quit - quit game\n");
			std::cout << ("force - computer will not think\n");
			std::cout << ("print - show board\n");
			std::cout << ("post - show thinking\n");
			std::cout << ("nopost - do not show thinking\n");
			std::cout << ("new - start new game\n");
			std::cout << ("setboard \"fen\" - set the board based on the provided fen\n");
			std::cout << ("go - set computer thinking\n");
			std::cout << ("depth x - set depth to x\n");
			std::cout << ("time x - set thinking time to x seconds (depth still applies if set)\n");
			std::cout << ("view - show current depth and movetime settings\n");
			std::cout << ("** note ** - to reset time and depth, set to 0\n");
			std::cout << ("enter moves using b7b8q notation\n\n\n");
			std::cout << std::flush;
		}
		else if (buf == "quit" || buf[0] == 'q')
		{
			this->info.quit = true;
			break;
		}
		else if(buf == "post")
		{
			this->info.doPrint = true;
		}
		else if(buf == "print")
		{
			IO::printBoard(pos);
		}
		else if(buf == "nopost")
		{
			this->info.doPrint = false;
		}
		else if(buf == "force")
		{
			engineSide = BOTH;
		}
		else if(buf == "view")
		{
			std::stringstream viewSS;
			if(depth == kMaxSearchDepth)
			{
				viewSS << "depth not set";
			}
			else
			{
				viewSS << "depth " << depth;
			}
			if(moveTime != 0)
			{
				viewSS << " movetime "<< (moveTime/1000)<<"s\n";
			}
			else 
			{
				viewSS << " movetime not set\n";
			}
			std::cout << viewSS.str();
		}
		else if (buf == "depth")
		{
			ss >> depth;
			if(depth == 0)
			{
				depth = kMaxSearchDepth;
			}
		}
		else if (buf == "time")
		{
			ss >> moveTime;
			moveTime *= Stopwatch::kMilliPerSecond;
		}
		else if (buf == "new")
		{
			engineSide = BLACK;
			this->pos.parseFEN(STARTFEN);
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
			engineSide = pos.side_to_move;
		}
		else if(buf == "undo")
		{
			// Go to previous user turn
			MM::takeMove(this->pos);
			MM::takeMove(this->pos);
			IO::printBoard(pos);
		}
		else if(buf == "eval")
		{
			IO::printBoard(this->pos);
			int32_t score1 = this->sa.eval.evaluatePosition(this->pos);
			std::cout << "Eval: " << score1 << std::endl;
			this->pos.flipBoard();
			IO::printBoard(this->pos);
			int32_t score2 = this->sa.eval.evaluatePosition(this->pos);
			std::cout << "Eval: " << score2<<std::endl;
		}
		else if (buf == "bookmove")
		{
			IO::printBoard(pos);
			Move m = Engine::getBook().getBookMove(this->pos);
			std::cout << m.toString()<< std::endl;
		}
		else
		{
			Move move = IO::parseMove(buf, this->pos);
			if(move.isNull())
			{
				std::cout << "Unrecognized Command: "<<buf<<'\n';
			}
			else 
			{
				MM::makeMove(this->pos, move);
				this->pos.ply = 0;
			}
		}
	}
}

int32_t ConsoleManager::getProtocol()
{
	return ProtocolManager::kConsole;
}