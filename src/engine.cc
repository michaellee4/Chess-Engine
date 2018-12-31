#include "engine.h"
#include "defs.h"
#include "init.h"
#include "uci.h"
#include "xboard.h"
#include "console.h"
#include "protocol.h"
#include <iostream>

Engine::Engine() noexcept: protocol(), config(), book()
{
	//Only ever called once because engine is a singleton
	Init::initAll();
	config.useBook = book.readBook();
}

void Engine::printGreeting() const noexcept
{
	std::cout << "C++ Chess Engine" << std::endl;
	std::cout << "Type \'console\' for an interactive console\n" << std::endl;
}

void Engine::start() noexcept
{
	this->printGreeting();
	bool gameOver = false;
	std::string buf;
	while(!gameOver)
	{
		std::cout << std::flush;
		if(!(getline (std::cin, buf))) { continue; }
		if(buf[0] == '\n') { continue; }
		if(buf == "uci")
		{
			this->protocol = std::make_unique<UCIManager>();
		}
		else if(buf == "xboard")
		{
			this->protocol = std::make_unique<XBoardManager>();
		}
		else if(buf == "console")
		{
			this->protocol = std::make_unique<ConsoleManager>();
		}
		else if(buf == "q" || buf == "quit")
		{
			gameOver = true;
		}
		if(this->protocol)
		{
			this->protocol->loop();
			gameOver = this->protocol->isOver();
		}
	}	
}
