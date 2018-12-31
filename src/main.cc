#include "engine.h"
#include "tester.h"
#include "stopwatch.h"
#include "bitboard.h"
#include <iostream>
void runTest()
{
	Engine::getInstance();
	Board b;
	PerftTester p;
	Stopwatch s;
	s.start();
	p.perftTest(6, b, true);
	std::cout<< s.stop()<<std::endl;
}
using namespace std;
int main()
{
	// Engine& engine = Engine::getInstance();
	// engine.start();
	runTest();
	return 0;
}
