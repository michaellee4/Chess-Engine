#include "defs.h"
#include <iostream>
#include <iomanip>
using namespace std;


void printArray()
{
	for(int i = 0; i < BRD_SQ_NUM; i++)
	{
		if(i%10 == 0)
			cout<<endl;
		cout<<setfill(' ') << setw(5)<< Sq120ToSq64[i];
	}	
	cout<<endl;
	cout<<endl;

	for(int i = 0; i < 64; i++)
	{
		if(i%8 == 0)
			cout<<endl;
		cout<<setfill(' ') << setw(5)<< Sq64ToSq120[i];
	}
	cout<<endl;

}


int main()
{
	InitAll();
	printArray();
	return 0;
}