#include <iostream>
#include <fstream>
#include <string>
#include "Input.h"
#include "Matrix.h"
using namespace std;
int main() 
{
	setlocale(LC_ALL, "RUS");
	ifstream input("input.txt");
	List<string>* Flights = new List<string>();
	string From;
	string To;

	Input(Flights, input);
	cout << "All Flights:" << endl;
	for (int i = 0; i < Flights->get_size(); i++)
		cout << Flights->at(i) << endl;

	cout << "\nFrom: ";
	getline(cin, From);
	cout << "  To: ";
	getline(cin, To);

	Matrix* matrix = new Matrix(Flights);
	cout << matrix->Floyd_Warshall(From, To) << endl;
	system("pause");
}