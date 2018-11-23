#include "defs.h"
#include <cstdio>
#include "perft.h"
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


void PerftTester::PerftTest(uint32_t depth, Board& pos) {

    // ASSERT(CheckBoard(pos));

	pos.PrintBoard();
	printf("\nStarting Test To Depth:%d\n",depth);	
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
        printf("move %d : %s : %ld\n",MoveNum+1,move.ToString().c_str(),oldnodes);
    }
	
	printf("\nTest Complete : %ld nodes visited\n",this->leafNodes);

    return;
}

void PerftTester::PerftTestAll(Board& pos)
{

}