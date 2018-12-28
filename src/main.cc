#include "defs.h"
#include "bitboard.h"
#include "utils.h"
#include "init.h"
#include "hash.h"
#include "board.h"
#include "movelist.h"
#include "search.h"
#include "stopwatch.h"
#include "movemaker.h"
#include <cstdio>
#include <bitset>
#include "perft.h"
#include "io.h"
#include "searchinfo.h"
#include "search.h"
#include "uci.h"
#include "xboard.h"
#include "console.h"
#include <iostream>
#include <iomanip>
#include <unordered_set>
#include <climits>
#include <string>

#define PERFTFEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define pt "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define WAC1 "2rr3k/pp3pp1/1nnqbN1p/3pN3/2pP4/2P3Q1/PPB4P/R4RK1 w - -"
#define WAC2 "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1B3/PP3PPP/RN1QKB1R w KQkq - 0 1"

using namespace std;

void connect()
{
	bool gameOver = false;
	std::string buf;
	while(!gameOver)
	{
		std::cout << std::flush;
		if(!(getline (std::cin, buf))) { continue; }
		if(buf[0] == '\n') { continue; }
		if(buf == "uci")
		{
			UCIManager uci;
			uci.UCILoop();
			gameOver = uci.isOver();
		}
		else if(buf == "xboard")
		{
			XBoardManager xb;
			xb.XBoardLoop();
			gameOver = xb.isOver();
		}
		else if(buf == "console")
		{
			ConsoleManager cm;
			cm.consoleLoop();
			gameOver = cm.isOver();
		}
		else if(buf == "q" || buf == "quit")
		{
			gameOver = true;
		}
	}	
}

void printGreeting()
{
	std::cout << "C++ Chess Engine" << std::endl;
	std::cout << "Type \'console\' for an interactive console\n" << std::endl;
}
int main()
{
	Init::initAll();
	printGreeting();
	connect();
	// XBoardManager x;
	// x.XBoardLoop();
	// Board b(WAC2);
	// Board b;
	// PerftTester p;
	// Stopwatch s;
	// s.start();
	// p.perftTest(6,b,true);
	// p.perftTestAll(b);
	// std::cout << s.stop() << '\n';
	// gameLoop(b);
	// b.parseFEN("n1n5/PPPk4/8/8/8/8/4Kppp/5N1N w - - 0 1");	
	return 0;
}
