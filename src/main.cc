#include "defs.h"
#include <iostream>
#include <iomanip>
#include "bitboard.h"
#include "utils.h"
#include "init.h"
using namespace std;

int main()
{
	InitAll();
	
	for(int i = 0; i < 64; i++)
	{
		PrintBitBoard(ClearMask[i]);
		printf("\n");
	}
	return 0;
}