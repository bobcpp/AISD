#include <iostream>
#include <fstream>
#include "MaxFlow.h"
int main()
{
	try 
	{
		ifstream input("data.txt");
		Flow flow(input);
		std::cout << "\nMax flow is: " << flow.MaxFlow() << "\n";
	}
	catch (exception& exception) 
	{
		std::cout << exception.what();
	}
	return 0;
}