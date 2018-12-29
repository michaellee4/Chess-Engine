#include "engine.h"
using namespace std;
int main()
{
	Engine& engine = Engine::getInstance();
	engine.start();	
	return 0;
}
