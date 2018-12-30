#include "defs.h"
#include "tester.h"
#include "io.h"
#include "movelist.h"
#include "movemaker.h"
#include "move.h"
#include <fstream>
#include <iostream>
#include <sstream>
PerftTester::PerftTester() noexcept : leafNodes(0) {}

void PerftTester::perft(uint32_t depth, Board& pos) noexcept
{
    ASSERT(checkBoard(pos));  

	if(depth == 0) {
        ++this->leafNodes;
        return;
    }	

    MoveList m = pos.getAllMoves();
      
	for(uint32_t MoveNum = 0; MoveNum < m.size(); ++MoveNum) {	
       
        if ( !MM::makeMove(pos,m[MoveNum]))  {
            continue;
        }
        perft(depth - 1, pos);
        MM::takeMove(pos);
    }
}


int PerftTester::perftTest(uint32_t depth, Board& pos, bool print = true) noexcept
 {
    ASSERT(checkBoard(pos));
	if(print)
	{
		IO::printBoard(pos);
		std::cout << "\n" << "Starting Test To Depth: "<< depth << "\n";
	}
	this->leafNodes = 0;

    MoveList m = pos.getAllMoves();
    
	for(uint32_t MoveNum = 0; MoveNum < m.size(); ++MoveNum) {
        Move move = m[MoveNum];
        if ( !MM::makeMove(pos, move))  {
            continue;
        }
        long cumnodes = this->leafNodes;
        perft(depth - 1, pos);
        MM::takeMove(pos);        
        long oldnodes = this->leafNodes - cumnodes;
		if(print)
    		std::cout << "move " << MoveNum + 1 << " : " << move.toString() << " : " << oldnodes<<"\n";
	}
	if(print)
		std::cout << "\n" << "Test Complete : " << this->leafNodes << " nodes visited" << "\n";
    return this->leafNodes;
}

void PerftTester::perftTestAll(Board& pos) noexcept
{
	
	std::ifstream perftFile("tests/perftsuite.epd");
	std::string linebuf;
	std::string fen;
	char buf;
	int depth;
	int expected;
	
	if (perftFile.is_open())
	{
		while (getline(perftFile, linebuf))
		{
			std::stringstream line(linebuf);
			getline(line, fen, ';');
			std::cout << "Testing fen: "<< fen <<";";
			pos.parseFEN(fen);
			while(line.good())
			{
				line >> buf;
				line >> depth;
				line >> expected;
				line >> buf;
				if(depth <= 5)
				{
					int perft = perftTest(depth, pos, false);
					if(perft != expected)
					{
						std::cout << "mismatch at depth: " << depth << " got " << perft << " expected " << expected<< "\n";
					}
					std::cout<<'d'<<depth<<" "<<perft<<';';
				}
			}
			std::cout << "\n";
		}
		perftFile.close();
	}
	else std::cout << "cant open file" << "\n";
}
