#include "engine.h"

#include "perft.h"
#include "stopwatch.h"
#include "bitboard.h"
#include <iostream>

using namespace std;
int main()
{
	// Engine& engine = Engine::getInstance();
	// engine.start();	
	Engine::getInstance();
	Board b;
	PerftTester p;
	Stopwatch s;
	s.start();
	p.perftTest(6, b, true);
	std::cout<< s.stop()<<std::endl;
	return 0;
}
