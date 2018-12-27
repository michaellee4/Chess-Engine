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


void gameLoop(Board& b)
{
	SearchInfo info;
	SearchAgent s;

	// Game Loop
	std::string input;
	bool prevValid = true;
	while(true)
	{
		if(prevValid)
		{
			IO::printBoard(b);
		}
		cout<< "Please enter a move > ";
		cin >> input;
		if(input[0] == 'q') break;
		else if(input [0] == 't' && b.hist_ply == 0)
		{
			std::cout << "No Moves to Take!" << '\n';
			prevValid = false;
		} 
		else if(input[0] == 't')
		{
			MM::takeMove(b);
			prevValid = true;
		}
		else if (input[0] == 'p')
		{
			int max = PV_Table::getPvLine(b, 4);
			cout<< "PvLine of " << max << " Moves: ";
			for(int i = 0; i < max; i++)
			{
				Move move = b.pv_arr[i];
				cout << move.toString() << " ";
			}
			cout << '\n';
			prevValid = true;
		}
		else if(input[0] == 's')
		{
			info.depth = 6;
			info.startTime = Stopwatch::getTimeInMilli();
			info.stopTime = info.startTime + 200000;
			s.searchPosition(b, info);
			prevValid = false;
		}
		else 
		{
			Move move = IO::parseMove(input, b);
			if(move.move != 0)
			{
				b.pv_table.insert(b, move);
				if(!MM::makeMove(b, move))
				{
					cout << "Illegal Move!"<<'\n';
					prevValid = true;
				}
				else
					prevValid = true;
			}
			else
			{
				std::cout << "Illegal Move!" << '\n';
				prevValid = false;
			}
		}
	}
}

int main()
{
	Init::initAll();
	UCIManager uci;
	// Board b(WAC2);
	// Board b;
	// PerftTester p;
	// Stopwatch s;
	// s.start();
	uci.UCILoop();
	// p.perftTest(6,b,true);
	// p.perftTestAll(b);
	// std::cout << s.stop() << '\n';
	// gameLoop(b);
	// b.parseFEN("n1n5/PPPk4/8/8/8/8/4Kppp/5N1N w - - 0 1");	
	return 0;
}
