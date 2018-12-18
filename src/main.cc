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
#include "stopwatch.h"
#include "movemaker.h"
#include <cstdio>
#include <bitset>
#include "perft.h"
#include "io.h"
#include <climits>
#include <string>
#define PERFTFEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define pt "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

using namespace std;

int main()
{
	InitAll();


	Board b;
	MoveList m;
	std::string input;
	b.ParseFEN("n1n5/PPPk4/8/8/8/8/4Kppp/5N1N w - - 0 1");	
	ASSERT(CheckBoard(b));

	// Game Loop
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
		else 
		{
			Move move = IOHandler::ParseMove(input, b);
			if(move.move != 0)
			{
				cout<< "making move: " << move.From() <<" "<<move.To() <<endl;
				MM::MakeMove(b, move);
				prevValid = true;
			}
			else
			{
				std::cout << "Illegal Move!" << std::endl;
				prevValid = false;
			}
		}
	}
	return 0;
}
