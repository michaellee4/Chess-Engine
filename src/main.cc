#include "defs.h"
#include <iostream>
#include <iomanip>
#include "bitboard.h"
#include "utils.h"
#include "init.h"
#include "hash.h"
#include "board.h"
#include "movelist.h"
#include <unordered_set>
#include "search.h"
#include "stopwatch.h"
#include "movemaker.h"
#include <cstdio>
#include <bitset>
#include "perft.h"
#include "io.h"
#include <climits>
#include <string>
#include "searchinfo.h"
#include "search.h"
#define PERFTFEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define pt "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define WAC1 "2rr3k/pp3pp1/1nnqbN1p/3pN3/2pP4/2P3Q1/PPB4P/R4RK1 w - -"

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
			IOHandler::PrintBoard(b);
		}
		cout<< "Please enter a move > ";
		cin >> input;
		if(input[0] == 'q') break;
		else if(input [0] == 't' && b.hist_ply == 0)
		{
			std::cout << "No Moves to Take!" << std::endl;
			prevValid = false;
		} 
		else if(input[0] == 't')
		{
			MM::TakeMove(b);
			prevValid = true;
		}
		else if (input[0] == 'p')
		{
			int max = PV_Table::getPvLine(b, 4);
			cout<< "PvLine of " << max << " Moves: ";
			for(int i = 0; i < max; i++)
			{
				Move move = b.pv_arr[i];
				cout << move.ToString() << " ";
			}
			cout << endl;
			prevValid = true;
		}
		else if(input[0] == 's')
		{
			info.depth = 4;
			s.searchPosition(b, info);
			prevValid = false;
		}
		else 
		{
			Move move = IOHandler::ParseMove(input, b);
			if(move.move != 0)
			{
				b.pv_table.insert(b, move);
				if(!MM::MakeMove(b, move))
				{
					cout << "Illegal Move!"<<std::endl;
					prevValid = true;
				}
				else
					prevValid = true;
			}
			else
			{
				std::cout << "Illegal Move!" << std::endl;
				prevValid = false;
			}
		}
	}
}

int main()
{
	InitAll();
	Board b(WAC1);
	PerftTester p;
	// p.PerftTestAll(b);
	gameLoop(b);
	// b.ParseFEN("n1n5/PPPk4/8/8/8/8/4Kppp/5N1N w - - 0 1");	
	return 0;
}
