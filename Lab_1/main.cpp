#include <iostream>
#include "map.h"

int main()
{
	map<int, int> x;
	for (int i = 0; i < 7; i++)
	{
		x.insert(i*3, i*2);
	}
	x.print();
}