#include "defs.h"
#include "perft.h"
#include <fstream>
#include <iostream>
#include <sstream>
void PerftTester::Perft(uint32_t depth, Board& pos) {

    // ASSERT(CheckBoard(pos));  

	if(depth == 0) {
        ++this->leafNodes;
        return;
    }	

    MoveList m;
    m.GenerateAllMoves(pos);
      
	for(uint32_t MoveNum = 0; MoveNum < m.moves.size(); ++MoveNum) {	
       
        if ( !MM::MakeMove(pos,m.moves[MoveNum]))  {
            continue;
        }
        Perft(depth - 1, pos);
        MM::TakeMove(pos);
    }

    return;
}


int PerftTester::PerftTest(uint32_t depth, Board& pos, bool print = true) {

    // ASSERT(CheckBoard(pos));
	
	if(print)
	{
		pos.PrintBoard();
		std::cout << std::endl << "Starting Test To Depth: "<< depth << std::endl;
	}
	this->leafNodes = 0;

    MoveList m;
    m.GenerateAllMoves(pos);
    
	for(uint32_t MoveNum = 0; MoveNum < m.moves.size(); ++MoveNum) {
        Move move = m.moves[MoveNum];
        if ( !MM::MakeMove(pos, move))  {
            continue;
        }
        long cumnodes = this->leafNodes;
        Perft(depth - 1, pos);
        MM::TakeMove(pos);        
        long oldnodes = this->leafNodes - cumnodes;
		if(print)
    		std::cout << "move " << MoveNum + 1 << " : " << move.ToString() << " : " << oldnodes<<std::endl;
	}
	if(print)
		std::cout << std::endl << "Test Complete : " << this->leafNodes << " nodes visited" << std::endl;
    return this->leafNodes;
}

void PerftTester::PerftTestAll(Board& pos)
{
	
	std::ifstream perftFile("src/test/perftsuite.epd");
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
			std::cout << "Testing fen: "<< fen <<std::endl;
			pos.ParseFEN(fen);
			while(line.good())
			{
				line >> buf;
				line >> depth;
				line >> expected;
				line >> buf;
				if(depth <= 5)
				{
					int perft = PerftTest(depth, pos, false);
					if(perft != expected)
					{
						std::cout << "mismatch at depth: " << depth << " got " << perft << " expected " << expected<< std::endl;
					}
				}
			}
		}
		perftFile.close();
	}
	else std::cout << "cant open file" << std::endl;
}
