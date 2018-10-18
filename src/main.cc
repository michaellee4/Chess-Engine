#include "defs.h"
#include <iostream>
#include <iomanip>
#include "bitboard.h"
#include "utils.h"
#include "init.h"
#include "hash.h"
#include <unordered_set>
using namespace std;

int main()
{
	InitAll();
	
	unordered_set<U64> s; 
	int numDup = 0;
	for(int i = 0; i < 100; i++)
	{
		U64 r = RandU64();
		if(s.find(r)!=s.end())
			numDup++;
		s.insert(r);
		printf("%llu\n", r);
	}
	return 0;
}